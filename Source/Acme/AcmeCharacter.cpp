// Copyright Epic Games, Inc. All Rights Reserved.

#include "AcmeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "StatComponent.h"
#include "AI_Main.h"
#include "Widget_Hud.h"
#include "Util.h"
#include "ActorInteractive.h"
#include "Actor_Projectile.h"
#include "Sound/SoundBase.h"
#include "Actor_Weapon.h"
#include "CharacterMonster.h"


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

	StatCompoenent = CreateDefaultSubobject<UStatComponent>(TEXT("StatCompoenent"));
	PrimaryActorTick.bCanEverTick = true;

	ComboIdx = 0;
	CanAttack = true;

	ActiveElement = EElement::E_Normal;
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
		Hud->SetStamina(StatCompoenent->GetCurrentStamina());

		Hud->BindStatus(StatCompoenent);

		StatCompoenent->OnChangedStamina.AddUObject(this, &AAcmeCharacter::StaminaCheck);
	}

	AnimInstance = Cast<UAI_Main>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &AAcmeCharacter::EndAttack);
	AnimInstance->OnEquip.AddUObject(this, &AAcmeCharacter::EquipWeapon);
	AnimInstance->OnDismantle.AddUObject(this, &AAcmeCharacter::DismantleWeapon);
	AnimInstance->OnAttackStart.AddUObject(this, &AAcmeCharacter::AttackStart);
	AnimInstance->OnAttackEnd.AddUObject(this, &AAcmeCharacter::AttackEnd);
	AnimInstance->OnInteract.AddUObject(this, &AAcmeCharacter::Interact);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FRotator rotator;
	FVector  SpawnLocation = GetActorLocation();
	SpawnLocation.Z += 100;

	Weapon = GetWorld()->SpawnActor<AActor_Weapon>(WeaponClass, SpawnLocation, rotator, SpawnParams);
	if (Weapon)
	{
		Weapon->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Weapon->Dismantle();
	}
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::Jump);
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
		EnhancedInputComponent->BindAction(JumpDashAttack, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartJampDashAttack);
	
		//Skill
		EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartSkill);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartInteract);
			
		//Equip
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::ChangeEquip);
	
		//Element
		EnhancedInputComponent->BindAction(Element1Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::SetActiveElementOne);
		EnhancedInputComponent->BindAction(Element2Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::SetActiveElementTwo);
		EnhancedInputComponent->BindAction(Element3Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::SetActiveElementThree);
		EnhancedInputComponent->BindAction(Element4Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::SetActiveElementFour);
	}
}

void AAcmeCharacter::Move(const FInputActionValue& Value)
{
	if (IsAttacking)
	{
		AnimInstance->StopAllMontages(-1.f);
	}

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

void AAcmeCharacter::Jump()
{
	if (IsAttacking) return;

	Super::Jump();
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

	GetWorldTimerManager().ClearTimer(StaminaRecoveryTimer);
	GetWorldTimerManager().SetTimer(StaminaRecoveryTimer,
		FTimerDelegate::CreateLambda([this]() {
			StatCompoenent->RecoveryStamina(100);
			}),
		5.f, true);

	if (IsCombo)
	{
		//combo
		ComboIdx = (ComboIdx + 1) % 3;
		AttackQueue.Enqueue(ComboIdx);

		return;
	}

	IsAttacking = true;
	IsCombo = true;

	AttackQueue.Enqueue(ComboIdx);
	FlushQueue();
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
	FString MontageName = Montage->GetName();

	if (!AttackQueue.IsEmpty())
	{
		FlushQueue();
	}
	else
	{
		IsCombo = false;
		IsAttacking = false;
		ComboIdx = 0;
	}

	if (MontageName == TEXT("AM_Attack") || MontageName == TEXT("AM_JDAttack"))
	{
		if (!bInterrupted)
		{
			StatCompoenent->ConsumeStamina(10/*TODO:var*/);
		}
	}

	if (MontageName == TEXT("AM_Exhaust"))
	{
		//stamina recovery
		StatCompoenent->RecoveryStamina(100);
		CanAttack = true;
		ChangeWalkSpeed(100);
	}
}

void AAcmeCharacter::StartJampDashAttack()
{
	if (AnimState == EAnimState::E_Unarmed) return;
	IsAttacking = true;

	StartDash();
	AnimInstance->PlayJumpDashAttack();
}

void AAcmeCharacter::StartSkill()
{
}

void AAcmeCharacter::StartInteract()
{
	if (!OverlapActor.IsValid()) return;
	if (!AnimInstance) return;

	AnimInstance->PlayInteract();
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

void AAcmeCharacter::EquipWeapon()
{
	if (!Weapon) return;
	Weapon->Equip();
}

void AAcmeCharacter::DismantleWeapon()
{
	if (!Weapon) return;
	Weapon->Dismantle();
}

void AAcmeCharacter::AttackStart()
{
	GetWorldTimerManager().SetTimer(OUT AttackTimer, this, &AAcmeCharacter::AttackCheck, .01f, true);
}

void AAcmeCharacter::AttackEnd()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);

	for (AActor* Victim : VictimSet)
	{
		//Damage 계산(Victim쪽에서)
		auto Monster = Cast<ACharacterMonster>(Victim);
		if (!Monster) continue;

		Monster->SetTarget(this);
		Monster->OnAttacked(10, ActiveElement);
	}

	VictimSet.Empty();
}

void AAcmeCharacter::AttackCheck()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Query;

	Query.AddIgnoredActor(this);

	FVector StartPos = Weapon->GetWeponTopPos();
	FVector EndPos = Weapon->GetWeponEndPos();

	if (GetWorld()->SweepMultiByChannel(HitResults, StartPos, EndPos, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(12), Query))
	{
		for (auto Result : HitResults)
		{
			AActor* Victim = Result.GetActor();

			VictimSet.Add(Victim);
		}
	}
	//DrawDebugCapsule(GetWorld(), (StartPos + EndPos) / 2, (StartPos - EndPos).Length() / 2, 10, FRotationMatrix::MakeFromZ(Weapon->GetMesh()->GetRightVector()).ToQuat(), FColor::Red, false, 10.f, 0, 1.f);
}

void AAcmeCharacter::Interact()
{
	if (!OverlapActor.Get()) return;
	OverlapActor->Interact();
}

void AAcmeCharacter::StaminaCheck(int Stamina)
{
	if (Stamina == 0)
	{
		AnimInstance->PlayExhaust();

		CanAttack = false;
		ChangeWalkSpeed(-100 /*TODO: Var*/);
	}
}

void AAcmeCharacter::SetActiveElementOne()
{
	if (!StatCompoenent) return;
	ActiveElement = StatCompoenent->GetElementByNum(1);
	
	//TODO: fx
}

void AAcmeCharacter::SetActiveElementTwo()
{
	if (!StatCompoenent) return;
	ActiveElement = StatCompoenent->GetElementByNum(2);
}

void AAcmeCharacter::SetActiveElementThree()
{
	if (!StatCompoenent) return;
	ActiveElement = StatCompoenent->GetElementByNum(3);
}

void AAcmeCharacter::SetActiveElementFour()
{
	if (!StatCompoenent) return;
	ActiveElement = StatCompoenent->GetElementByNum(4);
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
		if (Hud) Hud->SetVisibleActionBorder(false);
		return;
	}

	if (OverlapActor != nullptr) OverlapActor->SetVisibleIndicator(false);
	OverlapActor = actor;
	OverlapActor->SetVisibleIndicator(true);
	if(Hud) Hud->SetVisibleActionBorder(true);
}

void AAcmeCharacter::ChangeWalkSpeed(float amount)
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	if (!Movement) return;

	Movement->MaxWalkSpeed += amount;
}

void AAcmeCharacter::AddElement(EElement element)
{
	if (!StatCompoenent) return;

	StatCompoenent->AddElement(element);
}
