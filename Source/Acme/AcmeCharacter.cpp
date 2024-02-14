// Copyright Epic Games, Inc. All Rights Reserved.

#include "AcmeCharacter.h"
#include "AcmeGameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneCaptureComponent2D.h"
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
#include "Acme/SwordActor.h"
#include "Acme/Interface/InteractableActor.h"

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

	UICameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("UICameraBoom"));
	UICameraBoom->SetupAttachment(RootComponent);
	UICameraBoom->TargetArmLength = 200; // The camera follows at this distance behind the character	

	UISceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("UISceneCapture"));
	UISceneCapture->SetupAttachment(UICameraBoom);

	StatCompoenent = CreateDefaultSubobject<UStatComponent>(TEXT("StatCompoenent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryCompoenent"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentCompoenent"));

	PrimaryActorTick.bCanEverTick = true;

	CanAttack = true;
	IsDodgeRoll = false;

	ActiveElement = EElement::E_End;

	IsOpenInven = false;
	CurrentQuickSlotIdx = 0;
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

	UISceneCapture->ShowOnlyComponent(GetMesh());

	AnimState = EAnimState::E_Unarmed;

	if (HudClass.Get() != nullptr)
	{
		Hud = CreateWidget<UWidget_Hud>(GetWorld(), HudClass);
		Hud->AddToViewport();

		//HUD Init
		Hud->SetHealth(StatCompoenent->GetCurrentHP(), StatCompoenent->GetMaxHP());
		Hud->SetSatiety(StatCompoenent->GetCurrentST());
		Hud->SetStamina(StatCompoenent->GetCurrentStamina());
		Hud->BindStatus(StatCompoenent);

		CurrentQuickSlotIdx = 0;

		Hud->SetQuickSlots(InventoryComponent->GetQuickSlots());
		Hud->ChangeSelectedSlot(CurrentQuickSlotIdx);

		StatCompoenent->OnChangedStamina.AddUObject(this, &AAcmeCharacter::StaminaCheck);
	}

	AnimInstance = Cast<UAI_Main>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &AAcmeCharacter::AnimEnd);
	AnimInstance->OnAttackStart.AddUObject(this, &AAcmeCharacter::StartSwordAttack);
	AnimInstance->OnAttackEnd.AddUObject(this, &AAcmeCharacter::EndSwordAttack);
	AnimInstance->OnInteract.AddUObject(this, &AAcmeCharacter::Interact);
	AnimInstance->OnDodgeRoll.AddUObject(this, &AAcmeCharacter::StopDodgeRoll);

	{
		FItem temp1;
		temp1.Name = EItemName::E_Sword;
		temp1.Num = 1;
		temp1.Category = EItemCategory::E_Equipment;
		temp1.bCanAddQuick = true;

		InventoryComponent->AddToInven(temp1, 2);
	}

	{
		FItem temp1;
		temp1.Name = EItemName::E_Helmet;
		temp1.Num = 1;
		temp1.Part = EEquipmentPart::E_Head;
		temp1.Category = EItemCategory::E_Equipment;
		temp1.bCanAddQuick = false;

		InventoryComponent->AddToInven(temp1, 1);
	}

	{
		FItem temp1;
		temp1.Name = EItemName::E_LetherArmor;
		temp1.Num = 1;
		temp1.Part = EEquipmentPart::E_Body;
		temp1.Category = EItemCategory::E_Equipment;
		temp1.bCanAddQuick = false;

		InventoryComponent->AddToInven(temp1, 0);
	}

	{
		FItem temp1;
		temp1.Name = EItemName::E_Fire;
		temp1.Num = 1;
		temp1.Category = EItemCategory::E_Element;
		temp1.bCanAddQuick = false;

		InventoryComponent->AddItem(temp1);
	}
	{
		FItem temp1;
		temp1.Name = EItemName::E_Water;
		temp1.Num = 5;
		temp1.bCanAddQuick = false;
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
	
		//Dodge
		EnhancedInputComponent->BindAction(DodgeRollAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartDodgeRoll);
		EnhancedInputComponent->BindAction(DodgeRollAction, ETriggerEvent::Completed, this, &AAcmeCharacter::StopDodgeRoll);
		
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AAcmeCharacter::EndSprint);
	
		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartActive);
		EnhancedInputComponent->BindAction(JumpDashAttack, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartJampDashAttack);
	
		//Skill
		EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartSkill);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::StartInteract);

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

		DodgeForward = MovementVector.Y;
		DodgeRight = MovementVector.X;
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

void AAcmeCharacter::StartDodgeRoll()
{
	auto Movement = GetCharacterMovement();
	if (!Movement || IsCrouch || IsDodgeRoll) return;
	if (!AnimInstance) return;

	IsDodgeRoll = true;

	AnimInstance->PlayDodgeRoll();
}

void AAcmeCharacter::StopDodgeRoll()
{
	IsDodgeRoll = false;
}

void AAcmeCharacter::StartActive()
{
	if (AnimState == EAnimState::E_Unarmed) return;
	if (!CanAttack) return;
	if (!EquipmentComponent) return;

	EquipmentComponent->Active(CurrentQuickSlotIdx);
}

void AAcmeCharacter::AnimEnd(UAnimMontage* Montage, bool bInterrupted)
{
	FString MontageName = Montage->GetName();

	if (MontageName == TEXT("AM_Attack") || MontageName == TEXT("AM_JDAttack"))
	{
		ASwordActor* Sword = Cast<ASwordActor>(EquipmentComponent->GetCurrentHand());
		if (Sword)
		{
			Sword->PlayCombo();
		}

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

	StartDodgeRoll();
	AnimInstance->PlayJumpDashAttack();
}

void AAcmeCharacter::StartSkill()
{
}

void AAcmeCharacter::StartInteract()
{
	//trace 가장 가까운 item -> Interact
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Query;

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation();
	EndLocation.Z += 100;

	ECollisionChannel ECC = ECollisionChannel::ECC_GameTraceChannel2;

	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(250);

	Query.AddIgnoredActor(this);
	if (GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::Identity, ECC, CollisionShape, Query))
	{
		for (auto HitResult : HitResults)
		{
			IInteractableActor* Interactable = Cast<IInteractableActor>(HitResult.GetActor());
			{
				if (Interactable) Interactable->Interact();
				return;
			}
		}
	}

	//FVector CenterOfSphere = ((EndLocation - StartLocation) / 2) + StartLocation;

	/*Draw the sphere in the viewport*/
	//DrawDebugSphere(GetWorld(), CenterOfSphere, CollisionShape.GetSphereRadius(), 10, FColor::Green, true);
}

void AAcmeCharacter::StartSwordAttack()
{
	if (!EquipmentComponent) return;

	ASwordActor* Sword = Cast<ASwordActor>(EquipmentComponent->GetCurrentHand());
	if (!Sword) return;

	Sword->BeginSeinsing();
}

void AAcmeCharacter::EndSwordAttack()
{
	if (!EquipmentComponent) return;

	ASwordActor* Sword = Cast<ASwordActor>(EquipmentComponent->GetCurrentHand());
	if (!Sword) return;

	Sword->EndSeinsing();
}

void AAcmeCharacter::StartSprint()
{
	if (IsSprint) return;

	IsSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = 900.f;

	StatCompoenent->StartSprint();
}

void AAcmeCharacter::EndSprint()
{
	IsSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	StatCompoenent->EndSprint();
}

void AAcmeCharacter::Interact()
{
	if (!OverlapActor.Get()) return;
	OverlapActor->Interact();
}

void AAcmeCharacter::ConsumeStamina(int amount)
{
	if (!StatCompoenent) return;

	StatCompoenent->ConsumeStamina(amount);
}

void AAcmeCharacter::PlaySwordAttack(int idx)
{
	if (!AnimInstance) return;
	AnimInstance->PlayAttack(idx);
}

void AAcmeCharacter::Equip(EEquipmentPart part, FItem item)
{
	if (!EquipmentComponent) return;

	EquipmentComponent->Equip(part, item);
	UpdateInventoryWidget();
}

void AAcmeCharacter::UnEquip(EEquipmentPart part)
{
	if (!EquipmentComponent) return;
	if (!InventoryWidget) return;

	EquipmentComponent->UnEquip(part);
	InventoryWidget->ClearEquip(part);
}

void AAcmeCharacter::SetShowInvenCam(UPrimitiveComponent* newMesh)
{
	if (!UISceneCapture) return;

	UISceneCapture->ShowOnlyComponent(newMesh);
}

bool AAcmeCharacter::IsCompleteQuest(FQuest quest)
{
	if (!InventoryComponent) return false;
	bool Result = true;

	for (FItem item : quest.Request)
	{
		Result = InventoryComponent->HasItem(item);
		if (Result == false) return Result;
	}

	return Result;
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
	ChangeQuickSlotIdx(0);
}

void AAcmeCharacter::QuickSlot2Start()
{
	ChangeQuickSlotIdx(1);
}

void AAcmeCharacter::QuickSlot3Start()
{
	ChangeQuickSlotIdx(2);
}

void AAcmeCharacter::QuickSlot4Start()
{
	ChangeQuickSlotIdx(3);
}

void AAcmeCharacter::QuickSlot5Start()
{
	ChangeQuickSlotIdx(4);
}

void AAcmeCharacter::QuickSlot6Start()
{
	ChangeQuickSlotIdx(5);
}

void AAcmeCharacter::QuickSlot7Start()
{
	ChangeQuickSlotIdx(6);
}

void AAcmeCharacter::QuickSlot8Start()
{
	ChangeQuickSlotIdx(7);
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

void AAcmeCharacter::SetAnimState(EAnimState newAnimState)
{
	AnimState = newAnimState;
}

void AAcmeCharacter::CloseInventory()
{
	auto PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;

	InventoryWidget->RemoveFromViewport();
	IsOpenInven = false;
}

void AAcmeCharacter::AddElement(EElement element)
{
	if (!InventoryComponent) return;

	FItem Item;
	Item.Category = EItemCategory::E_Element;
	//Item.Equiped = false;
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

	bool Result = InventoryComponent->AddItem(item);
	UpdateInventoryWidget();

	return Result;
}

void AAcmeCharacter::AddToInvenByIdx(FItem item, int idx)
{
	if (!InventoryComponent) return;

	InventoryComponent->AddToInven(item, idx);
	UpdateInventoryWidget();
}

void AAcmeCharacter::SwapInvenByIdx(FItem fromItem, int from, int to)
{
	if (!InventoryComponent) return;

	FItem toItem = InventoryComponent->GetItem(fromItem.Category, to);
	InventoryComponent->AddToInven(fromItem, to);
	InventoryComponent->AddToInven(toItem, from);
	UpdateInventoryWidget();
}

void AAcmeCharacter::SwapQuickByIdx(FItem fromItem, int from, int to)
{
	if (!InventoryComponent) return;

	FItem toItem = InventoryComponent->GetItem(fromItem.Category, to);
	SetQuickSlot(fromItem, to);
	SetQuickSlot(toItem, from);
}

void AAcmeCharacter::SwapQuickAndInven(FItem item, int quickIdx, int invenIdx)
{
	if (!InventoryComponent) return;

	FItem temp = InventoryComponent->GetItem(item.Category, invenIdx);
	InventoryComponent->AddToInven(item, invenIdx);
	SetQuickSlot(temp, quickIdx);
}

void AAcmeCharacter::UseItem(EItemCategory Category, int idx, int amount)
{
	if (!InventoryComponent) return;

	InventoryComponent->UseItem(Category, idx, amount);
	UpdateInventoryWidget();
}

void AAcmeCharacter::RemoveItem(EItemCategory Category, int idx)
{
	if (!InventoryComponent) return;

	InventoryComponent->RemoveFromInven(Category, idx);
	UpdateInventoryWidget();
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
	if (!EquipmentComponent) return;

	InventoryComponent->AddToQuick(item, idx);
	EquipmentComponent->SpawnItem(item, idx);

	if (idx == CurrentQuickSlotIdx)
	{
		EquipmentComponent->SetCurrentHand(idx);
	}

	//HUD Update
	if (!Hud) return;
	Hud->SetQuickSlots(GetQuickSlots());
	Hud->ChangeSelectedSlot(CurrentQuickSlotIdx);
}

void AAcmeCharacter::RemoveQuickSlot(int idx)
{
	if (!InventoryComponent) return;
	if (!EquipmentComponent) return;

	InventoryComponent->RemoveFromQuick(idx);
	EquipmentComponent->DestroyAttachActor(idx);

	if (idx == CurrentQuickSlotIdx)
	{
		EquipmentComponent->ClearCurrentHand();
	}

	if (!Hud) return;
	Hud->SetQuickSlots(GetQuickSlots());
}

void AAcmeCharacter::ChangeQuickSlotIdx(int idx)
{
	CurrentQuickSlotIdx = idx;

	//Equip Change
	if (!EquipmentComponent) return;
	EquipmentComponent->SetCurrentHand(CurrentQuickSlotIdx);

	//HUD Update
	if (!Hud) return;
	Hud->ChangeSelectedSlot(idx);

	//Anim
	if (!AnimInstance) return;
	AnimInstance->PlayEquip();
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
