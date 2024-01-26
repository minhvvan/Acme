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
#include "Acme/Component/StatComponent.h"
#include "Acme/Component/InventoryComponent.h"
#include "Acme/Animation/AI_Main.h"
#include "Acme/Widget/Widget_Hud.h"
#include "Acme/Utils/Util.h"
#include "ActorInteractive.h"
#include "Actor_Projectile.h"
#include "Sound/SoundBase.h"
#include "Actor_Weapon.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Kismet/GameplayStatics.h"
#include "Acme/Widget/InventoryWidget.h"
#include "Acme/Widget/AlchemicComposeWidget.h"
#include "Acme/Component/EquipmentComponent.h"

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
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryCompoenent"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentCompoenent"));

	PrimaryActorTick.bCanEverTick = true;

	ComboIdx = 0;
	CanAttack = true;

	ActiveElement = EElement::E_End;

	IsOpenInven = false;
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

		Hud->SetQuickSlots(InventoryComponent->GetQuickSlots());

		StatCompoenent->OnChangedStamina.AddUObject(this, &AAcmeCharacter::StaminaCheck);
	}

	AnimInstance = Cast<UAI_Main>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &AAcmeCharacter::EndAttack);
	AnimInstance->OnEquip.AddUObject(this, &AAcmeCharacter::AttachWeaponToHand);
	AnimInstance->OnDismantle.AddUObject(this, &AAcmeCharacter::AttachWeaponToBack);
	AnimInstance->OnAttackStart.AddUObject(this, &AAcmeCharacter::AttackStart);
	AnimInstance->OnAttackEnd.AddUObject(this, &AAcmeCharacter::AttackEnd);
	AnimInstance->OnInteract.AddUObject(this, &AAcmeCharacter::Interact);

	{
		FItem temp1;
		temp1.Name = EItemName::E_Sword;
		temp1.Num = 1;
		temp1.Equiped = false;
		temp1.Category = EItemCategory::E_Equipment;

		InventoryComponent->AddItem(temp1);
	}

	{
		FItem temp1;
		temp1.Name = EItemName::E_Fire;
		temp1.Num = 1;
		temp1.Equiped = false;
		temp1.Category = EItemCategory::E_Element;

		InventoryComponent->AddItem(temp1);
	}
	{
		FItem temp1;
		temp1.Name = EItemName::E_Water;
		temp1.Num = 1;
		temp1.Equiped = false;
		temp1.Category = EItemCategory::E_Element;

		InventoryComponent->AddItem(temp1);
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
	
		//QuickSlot
		EnhancedInputComponent->BindAction(Slot1Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::QuickSlot1Start);
		EnhancedInputComponent->BindAction(Slot2Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::QuickSlot2Start);
		EnhancedInputComponent->BindAction(Slot3Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::QuickSlot3Start);
		EnhancedInputComponent->BindAction(Slot4Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::QuickSlot4Start);
		EnhancedInputComponent->BindAction(Slot5Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::QuickSlot5Start);
		EnhancedInputComponent->BindAction(Slot6Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::QuickSlot6Start);
		EnhancedInputComponent->BindAction(Slot7Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::QuickSlot7Start);
		EnhancedInputComponent->BindAction(Slot8Action, ETriggerEvent::Triggered, this, &AAcmeCharacter::QuickSlot8Start);

		//Equip
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::OpenInventory);
	}
}

void AAcmeCharacter::Move(const FInputActionValue& Value)
{
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
		if (ComboIdx == 2) return;

		ComboIdx++;
		AttackQueue.Enqueue(ComboIdx);

		return;
	}

	IsAttacking = true;
	IsCombo = true;

	AttackQueue.Enqueue(ComboIdx);
	FlushQueue();
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
	//trace 가장 가까운 item -> Interact

	FHitResult HitResult;
	FCollisionQueryParams Query;

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation();
	EndLocation.Z += 100;

	ECollisionChannel ECC = ECollisionChannel::ECC_GameTraceChannel2;

	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(250);

	Query.AddIgnoredActor(this);
	if (GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, ECC, CollisionShape, Query))
	{
		AActorInteractive* Item = Cast<AActorInteractive>(HitResult.GetActor());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Name:%s"), *HitResult.GetActor()->GetName()));
		if (!Item) return;

		Item->Interact();
	}

	//FVector CenterOfSphere = ((EndLocation - StartLocation) / 2) + StartLocation;

	/*Draw the sphere in the viewport*/
	//DrawDebugSphere(GetWorld(), CenterOfSphere, CollisionShape.GetSphereRadius(), 10, FColor::Green, true);
}

void AAcmeCharacter::ChangeEquip()
{
	if (!EquipmentComponent) return;
	if (!EquipmentComponent->IsValidCurrnetWeapon()) return;

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

void AAcmeCharacter::AttachWeaponToHand()
{
	if (!EquipmentComponent) return;

	EquipmentComponent->EquipCurrentWeapon();
}

void AAcmeCharacter::AttachWeaponToBack()
{
	if (!EquipmentComponent) return;
	EquipmentComponent->DismantleCurrentWeapon();
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
	if (!EquipmentComponent) return;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Query;

	Query.AddIgnoredActor(this);

	//TODO: Comp로 빼야될지도 (전투시스템)
	FVector StartPos = EquipmentComponent->GetCurrentWeapon()->GetWeponTopPos();
	FVector EndPos = EquipmentComponent->GetCurrentWeapon()->GetWeponEndPos();

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

void AAcmeCharacter::OpenInventory()
{
	if (IsOpenInven || IsOpenInteractWidget) return;

	//open
	auto PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->SetPause(true);
	PC->bShowMouseCursor = true;

	if (InventoryWidget == nullptr)
	{
		InventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(), InventoryClass));
	}

	InventoryWidget->AddToViewport();
	IsOpenInven = true;
}

void AAcmeCharacter::QuickSlot1Start()
{
	//Attach Hand
}

void AAcmeCharacter::QuickSlot2Start()
{
}

void AAcmeCharacter::QuickSlot3Start()
{
}

void AAcmeCharacter::QuickSlot4Start()
{
}

void AAcmeCharacter::QuickSlot5Start()
{
}

void AAcmeCharacter::QuickSlot6Start()
{
}

void AAcmeCharacter::QuickSlot7Start()
{
}

void AAcmeCharacter::QuickSlot8Start()
{
}

void AAcmeCharacter::FlushQueue()
{
	if (!CanAttack)
	{
		AttackQueue.Empty();
		return;
	}

	if (!AttackQueue.IsEmpty())
	{
		int idx = *AttackQueue.Peek();
		AttackQueue.Pop();

		AnimInstance->PlayAttack(idx);
	}
}

void AAcmeCharacter::ShowOverlapInfo(bool bShow)
{
	if (!Hud) return;

	if (!bShow) Hud->SetVisibleActionBorder(false);
	else Hud->SetVisibleActionBorder(true);
}

void AAcmeCharacter::ChangeWalkSpeed(float amount)
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	if (!Movement) return;

	Movement->MaxWalkSpeed += amount;
}

void AAcmeCharacter::OnAttacked(int damage)
{
	if (!AnimInstance) return;
	AnimInstance->PlayAttacked();

	TakeDamage(damage);
}

void AAcmeCharacter::TakeDamage(int damage)
{
	if (!StatCompoenent) return;
	StatCompoenent->OnAttakced(damage);
}

void AAcmeCharacter::CloseInventory()
{
	auto PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeGameOnly());
	PC->SetPause(false);
	PC->bShowMouseCursor = false;

	InventoryWidget->RemoveFromViewport();
	IsOpenInven = false;
}

void AAcmeCharacter::AddElement(EElement element)
{
	if (!InventoryComponent) return;

	FItem Item;
	Item.Category = EItemCategory::E_Element;
	Item.Equiped = false;
	Item.Num = 1;

	switch (element)
	{
	case EElement::E_Fire:
		Item.Name = EItemName::E_Fire;
		break;
	case EElement::E_Water:
		Item.Name = EItemName::E_Water;
		break;
	case EElement::E_Earth:
		Item.Name = EItemName::E_Earth;
		break;
	case EElement::E_Air:
		Item.Name = EItemName::E_Air;
		break;
	case EElement::E_Ice:
		Item.Name = EItemName::E_Ice;
		break;
	case EElement::E_Thunder:
		Item.Name = EItemName::E_Thunder;
		break;
	}

	InventoryComponent->AddItem(Item);
}

FItemList& AAcmeCharacter::GetItems(EItemCategory category)
{
	FItemList temp = FItemList();
	if (!InventoryComponent) return temp;

	return InventoryComponent->GetItemList(category);
}

FItem AAcmeCharacter::GetItem(EItemCategory category, int idx)
{
	if (!InventoryComponent) return FItem();

	return InventoryComponent->GetItem(category, idx);
}

bool AAcmeCharacter::AddItem(FItem item)
{
	if (!InventoryComponent) return false;

	return InventoryComponent->AddItem(item);
}

void AAcmeCharacter::MoveItems(EItemCategory Category, int from, int to)
{
	if (!InventoryComponent) return;

	InventoryComponent->MoveItems(Category, from, to);
}

void AAcmeCharacter::UseItem(EItemCategory Category, int idx)
{
	if (!InventoryComponent) return;

	InventoryComponent->UseItem(Category, idx);
}

void AAcmeCharacter::UpdateInventoryWidget()
{
	if (!InventoryWidget) return;

	InventoryWidget->UpdateWidgetByCategory();
}

TArray<FItem> AAcmeCharacter::GetQuickSlots()
{
	if (!InventoryComponent) return TArray<FItem>();

	return InventoryComponent->GetQuickSlots();
}

void AAcmeCharacter::SetQuickSlot(FItem item, int idx)
{
	if (!InventoryComponent) return;

	InventoryComponent->SetQuickSlot(item, idx);

	//HUD Update
	if (!Hud) return;
	Hud->SetQuickSlots(GetQuickSlots());
}

void AAcmeCharacter::Equip(int idx)
{
	//Spawn Weapon
	if (!InventoryComponent) return;
	InventoryComponent->Equip(idx);

	if (!InventoryWidget) return;
	InventoryWidget->UpdateBorderToEquip(idx);
}

void AAcmeCharacter::Unequip(int idx)
{
	if (!InventoryComponent) return;
	InventoryComponent->Unequip(idx);

	if (!InventoryWidget) return;
	InventoryWidget->UpdateBorderToNoraml(idx);
}

void AAcmeCharacter::SetWeapon(FItem item)
{
	if (!EquipmentComponent) return;

	EquipmentComponent->SetCurrentWeapon(item);
}

void AAcmeCharacter::RemoveWeapon()
{
	if (!EquipmentComponent) return;

	EquipmentComponent->RemoveCurrentWeapon();
}

void AAcmeCharacter::DumpItem(EItemCategory Category, int idx)
{
	if (!InventoryComponent) return;
	InventoryComponent->Dump(Category, idx);

	if (!InventoryWidget) return;
	InventoryWidget->EmptyEntry(Category, idx);
}

void AAcmeCharacter::SetIsOpenWidget(bool bOpen)
{
	IsOpenInteractWidget = bOpen;
}

void AAcmeCharacter::CloseInteractWidget()
{
	//TODO: InteractWidget -> Super로 바꿔야함(요리나 다른 위젯이 있을 수 있음)
	if (!InteractWidget) return;

	auto PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeGameOnly());
	PC->SetPause(false);
	PC->bShowMouseCursor = false;

	InteractWidget->RemoveFromViewport();
	IsOpenInteractWidget = false;
}

void AAcmeCharacter::SetInteractWidget(UAlchemicComposeWidget* widget)
{
	InteractWidget = widget;
}
