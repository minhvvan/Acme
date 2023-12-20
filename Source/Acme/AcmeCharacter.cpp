// Copyright Epic Games, Inc. All Rights Reserved.

#include "AcmeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "AC_Stat.h"
#include "AI_Main.h"
#include "Widget_Hud.h"
#include "Util.h"
#include "ActorInteractive.h"
#include "Actor_Projectile.h"
#include "Sound/SoundBase.h"


//////////////////////////////////////////////////////////////////////////
// AAcmeCharacter

AAcmeCharacter::AAcmeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	StatCompoenent = CreateDefaultSubobject<UAC_Stat>(TEXT("StatCompoenent"));
	PrimaryActorTick.bCanEverTick = true;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));

	ComboTime = .5f;
	ComboIdx = 1;

	CanAttack = true;

	AttackCoolTime = 1.f;
}

void AAcmeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	StatCompoenent->CDDash.AddUObject(this, &AAcmeCharacter::CoolDownDash);

	AnimState = EAnimState::E_Unarmed;
	CanDash = true;

	if (HudClass.Get() != nullptr)
	{
		Hud = CreateWidget<UWidget_Hud>(GetWorld(), HudClass);
		Hud->AddToViewport();

		//HUD Init
		Hud->SetHealth(StatCompoenent->GetCurrentHP(), StatCompoenent->GetMaxHP());
		Hud->SetSatiety(StatCompoenent->GetCurrentST());

		Hud->BindStatus(StatCompoenent);
	}

	AnimInstance = Cast<UAI_Main>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AAcmeCharacter::EndAttack);
}

void AAcmeCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAcmeCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

//////////////////////////////////////////////////////////////////////////
// Input

void AAcmeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::Look);

		//Crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AAcmeCharacter::StopCrouch);
	
		//Crouch
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartDash);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &AAcmeCharacter::StopDash);
	
		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartAttack);
	
		//Skill
		EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartSkill);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartInteract);
			
		//Interact
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::ChangeEquip);
	}
}

void AAcmeCharacter::Move(const FInputActionValue& Value)
{
	if (IsAttacking) return;

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		DashForward = MovementVector.Y;
		DashRight = MovementVector.X;
	}
}

void AAcmeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		TurnRate = FMath::Clamp(LookAxisVector.X, -1.f, 1.f);
	}
}

void AAcmeCharacter::StartCrouch()
{
	auto Movement = GetCharacterMovement();
	if (!Movement || Movement->IsFalling()) return;

	IsCrouch = true;
	Crouch();
}

void AAcmeCharacter::StopCrouch()
{
	IsCrouch = false;
	UnCrouch();
}

void AAcmeCharacter::StartDash()
{
	auto Movement = GetCharacterMovement();
	if (!Movement || IsDashing || IsCrouch) return;
	if (!CanDash) return;

	IsDashing = true;

	FVector Dir;

	if (DashForward != 0)
	{
		Dir = GetActorForwardVector() * DashForward;
	}
	else
	{
		if (DashRight == 0) return;

		Dir = GetActorRightVector() * DashRight;
	}

	//scale
	Dir.X *= 1000;
	Dir.Y *= 1000;

	LaunchCharacter(Dir, false, false);

	CanDash = false;
	StatCompoenent->ExeDash();
}

void AAcmeCharacter::StopDash()
{
	auto Movement = GetCharacterMovement();
	if (!Movement) return;

	IsDashing = false;
}

void AAcmeCharacter::CoolDownDash()
{
	CanDash = true;
}

void AAcmeCharacter::StartAttack()
{
	if (AnimState == EAnimState::E_Unarmed) return;
	if (!CanAttack) return;

	if (IsCombo)
	{
		//combo
		GetWorldTimerManager().ClearTimer(ComboTimer);
		GetWorldTimerManager().SetTimer(ComboTimer,
			FTimerDelegate::CreateLambda([this]() {
				IsCombo = false;
				ComboIdx = 1;
				}),
			ComboTime, false);

		ComboIdx++;

		if (ComboIdx > 3)
		{
			//°ø°Ý ÄðÅ¸ÀÓ
			CanAttack = false;
			GetWorldTimerManager().SetTimer(AttackTimer, FTimerDelegate::CreateLambda([this]() {
					CanAttack = true;
				}),
				AttackCoolTime, true);
			return;
		}

		AttackQueue.Enqueue(ComboIdx);
		
		return;
	}

	GetWorldTimerManager().SetTimer(ComboTimer,
		FTimerDelegate::CreateLambda([this]() {
			IsCombo = false;
			ComboIdx = 1;
			}),
		ComboTime, false);

	IsAttacking = true;
	IsCombo = true;

	AttackQueue.Enqueue(ComboIdx);
	FlushQueue();

	//TODO: charge sfx
	AudioComp->SetSound(SFXCharge);
	AudioComp->Play();
}

void AAcmeCharacter::FireAttack()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	UCameraComponent* Cam = GetFollowCamera();
	FVector CamLoc = Cam->GetComponentLocation();
	FVector CamForward = Cam->GetForwardVector();

	FVector loc = GetMesh()->GetSocketLocation(FName(TEXT("Attack_Socket")));
	loc += CamForward * 100;
	
	FRotator rot = CamForward.Rotation();
	rot.Pitch += 10;

	AActor_Projectile* Projectile = GetWorld()->SpawnActor<AActor_Projectile>(ProjectileClass, loc, rot, SpawnParams);
}

void AAcmeCharacter::EndAttack(UAnimMontage* Montage, bool bInterrupted)
{
	if (!AttackQueue.IsEmpty())
	{
		FlushQueue();
	}
	else
	{
		IsAttacking = false;
	}
}

void AAcmeCharacter::StartSkill()
{
	//TODO: Current Skill execute
}

void AAcmeCharacter::StartInteract()
{
	//TODO: Current Overalp Actor -> Interact
	if (!OverlapActor.IsValid()) return;

	OverlapActor->Interact();
}

void AAcmeCharacter::ChangeEquip()
{
	if (AnimState == EAnimState::E_Unarmed)
	{
		AnimState = EAnimState::E_Equiped;

		if (!AnimInstance) return;
		AnimInstance->PlayEquip();
	}
	else
	{
		AnimState = EAnimState::E_Unarmed;

		if (!AnimInstance) return;

		AnimInstance->PlayDisMantle();
	}
}

bool AAcmeCharacter::FullCharged()
{
	Hud->SetCrosshairColor(FColor(51.f, 202.f, 255.f));

	if (AudioComp->IsPlaying())
	{
		AudioComp->Stop();
		AudioComp->SetSound(SFXComplete);
		AudioComp->Play();
	}

	return true;
}

void AAcmeCharacter::ResetCharge()
{
	Hud->SetPercent(0.f);
	Hud->SetCrosshairColor(FColor(255.f, 255.f, 255.f, 100.f));
	Ischarged = false;
}

void AAcmeCharacter::FlushQueue()
{
	if (!AttackQueue.IsEmpty())
	{
		int idx = *AttackQueue.Peek();
		AttackQueue.Pop();

		AnimInstance->PlayAttack(idx);
	}
}

void AAcmeCharacter::SetOverlapActor(AActorInteractive* actor)
{
	if (actor == nullptr)
	{
		if (OverlapActor != nullptr) OverlapActor->SetVisibleIndicator(false);
		OverlapActor.Reset();
		Hud->SetVisibleActionBorder(false);
		return;
	}

	if (OverlapActor != nullptr) OverlapActor->SetVisibleIndicator(false);
	OverlapActor = actor;
	OverlapActor->SetVisibleIndicator(true);
	Hud->SetVisibleActionBorder(true);
}
