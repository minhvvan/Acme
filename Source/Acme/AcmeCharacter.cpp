// Copyright Epic Games, Inc. All Rights Reserved.

#include "AcmeCharacter.h"
#include "Acme/Framework/AcmeGameInstance.h"
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
#include "Sound/SoundBase.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/Widget/InventoryWidget.h"
#include "Acme/Widget/AlchemicComposeWidget.h"
#include "Acme/Widget/DialogueWidget.h"
#include "Acme/Widget/GuideWidget.h"
#include "Acme/Component/EquipmentComponent.h"
#include "Acme/Component/QuestComponent.h"
#include "Acme/SwordActor.h"
#include "Acme/Interface/InteractableActor.h"
#include "Acme/Widget/RewardDialogueWidget.h"
#include "Acme/Widget/QuestNotCompleteWidget.h"
#include "GameFramework/PhysicsVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Acme/Widget/DeathWidget.h"
#include "Acme/Widget/PauseWidget.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Landscape/Classes/Landscape.h"
#include "GameFramework/PlayerStart.h"
#include "Acme/AcmePC.h"

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

	ThumbnailSceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("ThumbnailSceneCapture"));
	ThumbnailSceneCapture->SetupAttachment(CameraBoom);

	UICameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("UICameraBoom"));
	UICameraBoom->SetupAttachment(RootComponent);
	UICameraBoom->TargetArmLength = 200; // The camera follows at this distance behind the character	

	UISceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("UISceneCapture"));
	UISceneCapture->SetupAttachment(UICameraBoom);

	MiniMapCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMapCameraBoom"));
	MiniMapCameraBoom->SetupAttachment(RootComponent);
	MiniMapCameraBoom->TargetArmLength = 200; // The camera follows at this distance behind the character	

	MiniMapSceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMapSceneCapture"));
	MiniMapSceneCapture->SetupAttachment(MiniMapCameraBoom);

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->SetupAttachment(GetMesh());

	StatCompoenent = CreateDefaultSubobject<UStatComponent>(TEXT("StatCompoenent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryCompoenent"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentCompoenent"));
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));

	PrimaryActorTick.bCanEverTick = true;

	CanActive = true;
	IsDodgeRoll = false;

	IsOpenInven = false;
	CurrentQuickSlotIdx = 0;

	IsSwimming = false;
	bOpenGuide = true;
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
	AnimInstance->OnInteract.AddUObject(this, &AAcmeCharacter::Interact);
	AnimInstance->OnDodgeRoll.AddUObject(this, &AAcmeCharacter::StopDodgeRoll);
	AnimInstance->OnDeath.AddUObject(this, &AAcmeCharacter::Die);
	
	//Recipe
	{
		FRecipe recipe;

		{
			FItem temp;
			temp.Name = EItemName::E_Meat;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Food;

			recipe.Material.Add(temp);
		}

		{
			FItem temp;
			temp.Name = EItemName::E_Fruit;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Food;

			recipe.Material.Add(temp);
		}

		{
			FItem temp;
			temp.Name = EItemName::E_MeatPie;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Food;
			temp.bCanAddQuick = true;

			recipe.Result = temp;
		}

		OwnFoodRecipes.Add(recipe);
	}

	{
		FRecipe recipe;

		{
			FItem temp;
			temp.Name = EItemName::E_Glass;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Material;

			recipe.Material.Add(temp);
		}

		{
			FItem temp;
			temp.Name = EItemName::E_Herb;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Food;

			recipe.Material.Add(temp);
		}

		{
			FItem temp;
			temp.Name = EItemName::E_HealthPotion;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Potion;
			temp.bCanAddQuick = true;

			recipe.Result = temp;
		}

		OwnPotionRecipes.Add(recipe);
	}

	{
		FRecipe recipe;

		{
			FItem temp;
			temp.Name = EItemName::E_Metal;
			temp.Num = 2;
			temp.Category = EItemCategory::E_Material;

			recipe.Material.Add(temp);
		}

		{
			FItem temp;
			temp.Name = EItemName::E_Wood;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Material;

			recipe.Material.Add(temp);
		}

		{
			FItem temp;
			temp.Name = EItemName::E_Sword;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Equipment;
			temp.bCanAddQuick = true;

			recipe.Result = temp;
		}

		OwnCraftRecipes.Add(recipe);
	}

	{
		FRecipe recipe;

		{
			FItem temp;
			temp.Name = EItemName::E_Metal;
			temp.Num = 5;
			temp.Category = EItemCategory::E_Material;

			recipe.Material.Add(temp);
		}

		{
			FItem temp;
			temp.Name = EItemName::E_Helmet;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Equipment;

			recipe.Result = temp;
		}

		OwnCraftRecipes.Add(recipe);
	}

	{
		FRecipe recipe;

		{
			FItem temp;
			temp.Name = EItemName::E_Metal;
			temp.Num = 10;
			temp.Category = EItemCategory::E_Material;

			recipe.Material.Add(temp);
		}

		{
			FItem temp;
			temp.Name = EItemName::E_LetherArmor;
			temp.Num = 1;
			temp.Category = EItemCategory::E_Equipment;

			recipe.Result = temp;
		}

		OwnCraftRecipes.Add(recipe);
	}
}

void AAcmeCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Ongoing, this, &AAcmeCharacter::SwimUP);
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
		EnhancedInputComponent->BindAction(DodgeRollAction, ETriggerEvent::Ongoing, this, &AAcmeCharacter::SwimDown);
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
	
		//ESC
		EnhancedInputComponent->BindAction(ESCAction, ETriggerEvent::Triggered, this, &AAcmeCharacter::OpenPauseMenu);
	}
}

void AAcmeCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (!IsSwimming)
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
		else
		{
			AddMovementInput(GetControlRotation().Vector());
		}
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
	if (!IsSwimming)
	{
		if (JumpSFX && GetCharacterMovement()->MovementMode != EMovementMode::MOVE_Falling)
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), JumpSFX, GetActorLocation());
		}

		Super::Jump();
	}
	else
	{
		AddMovementInput(GetActorUpVector());
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

void AAcmeCharacter::StartDodgeRoll()
{
	if (IsSwimming) return;
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
	if (!CanActive) return;
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
		CanActive = true;
		ChangeWalkSpeed(100);
	}
}

void AAcmeCharacter::StartJampDashAttack()
{
	if (AnimState == EAnimState::E_Unarmed) return;

	StartDodgeRoll();
	AnimInstance->PlayJumpDashAttack();
}

void AAcmeCharacter::StartSkill()
{
}

void AAcmeCharacter::StartInteract()
{
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
			if (Interactable)
			{
				Interactable->Interact();
				return;
			}
		}
	}
}

void AAcmeCharacter::StartSwordAttack()
{
	if (!EquipmentComponent) return;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Query;

	Query.AddIgnoredActor(this);
	ASwordActor* Sword = Cast<ASwordActor>(EquipmentComponent->GetCurrentHand());
	if(Sword) Query.AddIgnoredActor(Sword);

	FVector StartPos = GetMesh()->GetSocketLocation(FName(TEXT("AttackStartPos")));
	FVector EndPos = GetMesh()->GetSocketLocation(FName(TEXT("AttackEndPos")));
	
	if (GetWorld()->SweepMultiByChannel(HitResults, StartPos, EndPos, GetActorQuat(), ECC_Pawn, FCollisionShape::MakeSphere(100), Query))
	{
		for (auto Result : HitResults)
		{
			ACharacterMonster* Monster = Cast<ACharacterMonster>(Result.GetActor());
			if (!Monster) continue;

			Monster->SetTarget(this);
			Monster->OnAttacked(StatCompoenent->GetStrength());
		}
	}
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
	//if (!OverlapActor.Get()) return;
	//OverlapActor->Interact();
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
	if (!InventoryWidget) InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryClass);

	EquipmentComponent->Equip(part, item);
	UpdateInventoryWidget();
	InventoryWidget->SetEquipSlot(part, item);
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

void AAcmeCharacter::ShowDialogWidget(FQuest quest)
{
	if(!DialogueWidget) DialogueWidget = Cast<UDialogueWidget>(CreateWidget(GetWorld(), DialogueWidgetClass));
	DialogueWidget->AddToViewport();
	DialogueWidget->SetQuestInfo(quest);

	auto PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;
}

void AAcmeCharacter::ShowRewardWidget(FQuest quest)
{
	if (!RewardWidget) RewardWidget = Cast<URewardDialogueWidget>(CreateWidget(GetWorld(), RewardWidgetClass));
	RewardWidget->AddToViewport();
	RewardWidget->SetQuestInfo(quest);

	auto PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;
}

void AAcmeCharacter::ShowNotComleteWidget(FQuest quest)
{
	if (!NotCompleteWidget) NotCompleteWidget = Cast<UQuestNotCompleteWidget>(CreateWidget(GetWorld(), NotCompleteWidgetClass));
	NotCompleteWidget->AddToViewport();
	NotCompleteWidget->SetQuestInfo(quest);

	auto PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;

}

void AAcmeCharacter::AddQuest(FQuest quest)
{
	if (!QuestComponent) return;
	if (!Hud) return;
	QuestComponent->AddQuest(quest);
	Hud->AddQuest(quest);

	OnAcceptQuest.Broadcast(quest.QusetID);
}

TArray<FRecipe> AAcmeCharacter::GetFoodRecipes()
{
	return OwnFoodRecipes;
}

TArray<FRecipe> AAcmeCharacter::GetPotionRecipes()
{
	return OwnPotionRecipes;
}

TArray<FRecipe> AAcmeCharacter::GetCraftRecipes()
{
	return OwnCraftRecipes;
}

void AAcmeCharacter::AddRecipe(FRecipe newRecipe)
{
	OwnFoodRecipes.Add(newRecipe);
}

int AAcmeCharacter::GetItemNums(FItem item)
{
	if (!InventoryComponent) return false;
	int Result = 0;

	Result = InventoryComponent->GetItemNums(item);
	return Result;
}

void AAcmeCharacter::AddSatiety(int amount)
{
	if (!StatCompoenent) return;

	StatCompoenent->AddSatiety(amount);
}

void AAcmeCharacter::Heal(int amount)
{
	//TODO: FX

	if (!StatCompoenent) return;
	StatCompoenent->Heal(amount);
}

void AAcmeCharacter::ConsumeItemQuick()
{
	if (!EquipmentComponent) return;
	if (!InventoryComponent) return;

	InventoryComponent->ConsumeQuickSlot(CurrentQuickSlotIdx);
	EquipmentComponent->ConsumeCurrentHand();

	//HUD Update
	if (!Hud) return;
	Hud->SetQuickSlots(GetQuickSlots());
	Hud->ChangeSelectedSlot(CurrentQuickSlotIdx);
}

void AAcmeCharacter::RemoveQuestList(int questID)
{
	Hud->RemoveQuest(questID);
}

void AAcmeCharacter::StartSwim()
{
	GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = true;

	FVector Dir = UKismetMathLibrary::GetUpVector(GetControlRotation()) * 20;
	Dir += UKismetMathLibrary::GetForwardVector(GetControlRotation()) * 20;

	LaunchCharacter(Dir, false, false);
	
	IsSwimming = true;
}

void AAcmeCharacter::StopSwim()
{
	GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = false;
	IsSwimming = false;
}

void AAcmeCharacter::SwimUP()
{
	if (!IsSwimming) return;
	AddMovementInput(GetActorUpVector());
}

void AAcmeCharacter::SwimDown()
{
	if (!IsSwimming) return;
	AddMovementInput(-1*GetActorUpVector());
}

void AAcmeCharacter::Burn(ACharacterMonster* causer)
{
	ClearBurnTimer();

	Niagara->SetActive(true);
	if (BurnSFX) 
	{
		BurnAudio = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BurnSFX, GetActorLocation());
	}

	GetWorldTimerManager().SetTimer(BurnTimer, FTimerDelegate::CreateLambda([this, causer]() {
		TakeDamage(2, causer);
		}), 1.f, true);

	GetWorldTimerManager().SetTimer(BurnEndTimer, FTimerDelegate::CreateLambda([this]() {
		ClearBurnTimer();
		Niagara->Deactivate();
		}), 5.f, false);
}

void AAcmeCharacter::ClearBurnTimer()
{
	if (BurnAudio)
	{
		BurnAudio->Stop();
		BurnAudio = nullptr;
	}

	GetWorldTimerManager().ClearTimer(BurnTimer);
	GetWorldTimerManager().ClearTimer(BurnEndTimer);
}

void AAcmeCharacter::DeathAnimStart()
{
	if(!AnimInstance) AnimInstance = Cast<UAI_Main>(GetMesh()->GetAnimInstance());
	CanActive = false;

	AnimInstance->PlayDeath();
}

void AAcmeCharacter::Die()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	DeathWidget = Cast<UDeathWidget>(CreateWidget(GetWorld(), DeathWidgetClass));
	DeathWidget->AddToViewport();

	auto PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;
}

void AAcmeCharacter::MoveToLobby()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Lobby")));
	if (Hud)
	{
		Hud->RemoveFromParent();
	}
}

int AAcmeCharacter::GetCurrentHP()
{
	if (!StatCompoenent) return 100;
	return StatCompoenent->GetCurrentHP();
}

int AAcmeCharacter::GetCurrentSatiety()
{
	if (!StatCompoenent) return 100;
	return StatCompoenent->GetCurrentST();
}

void AAcmeCharacter::SetCurrentHP(int newHP)
{
	if (!StatCompoenent) return;
	StatCompoenent->SetCurrentHP(newHP);
}

void AAcmeCharacter::SetCurrentSatiety(int newST)
{
	if (!StatCompoenent) return;
	StatCompoenent->SetCurrentST(newST);
}

void AAcmeCharacter::SetInventory(TMap<EItemCategory, FItemList> inven)
{
	if (!InventoryComponent) return;
	InventoryComponent->InitInventory(inven);
}

TMap<EItemCategory, FItemList> AAcmeCharacter::GetInventory()
{
	if (!InventoryComponent) return TMap<EItemCategory, FItemList>();
	return InventoryComponent->GetAllInventory();
}

FItem AAcmeCharacter::GetCurrentHead()
{
	if (!EquipmentComponent) return FItem();
	return EquipmentComponent->GetCurrentHead();
}

FItem AAcmeCharacter::GetCurrentBody()
{
	if (!EquipmentComponent) return FItem();
	return EquipmentComponent->GetCurrentBody();
}

FItem AAcmeCharacter::GetCurrentAcc()
{
	if (!EquipmentComponent) return FItem();
	return EquipmentComponent->GetCurrentAcc();
}

USceneCaptureComponent2D* AAcmeCharacter::GetThumbnailSceneCapture()
{
	return ThumbnailSceneCapture;
}

void AAcmeCharacter::RespawnCharacter()
{
	if (Hud) Hud->RemoveFromParent();
	//Transfer Inventory

	AAcmePC* PC = Cast<AAcmePC>(GetController());
	PC->UnPossess();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	auto PlayerStart = Cast<APlayerStart>(FoundActors[0]);

	if (PlayerStart)
	{
		FVector Pos = PlayerStart->GetActorLocation();
		Pos.Z += 500;

		AAcmeCharacter* Character = GetWorld()->SpawnActor<AAcmeCharacter>(CharacterClass, Pos, FRotator::ZeroRotator);
		Character->SetInventory(GetInventory());
		Character->SetQuickSlots(GetQuickSlots());

		PC->Possess(Character);
	}

	Destroy();
}

void AAcmeCharacter::SetbOpenGuide(bool open)
{
	bOpenGuide = open;
}

bool AAcmeCharacter::GetbOpenGuide()
{
	return bOpenGuide;
}

void AAcmeCharacter::StaminaCheck(int Stamina)
{
	if (Stamina == 0)
	{
		if (!AnimInstance) AnimInstance = Cast<UAI_Main>(GetMesh()->GetAnimInstance());
		AnimInstance->PlayExhaust();

		CanActive = false;
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

void AAcmeCharacter::Restart()
{
	Super::Restart();

	if (!StatCompoenent) return;
	StatCompoenent->Init();

	StopCrouch();
}

void AAcmeCharacter::OpenPauseMenu()
{
	if (PauseMenuWidget == nullptr)
	{
		PauseMenuWidget = Cast<UPauseWidget>(CreateWidget(GetWorld(), PauseMenuWidgetClass));
	}

	PauseMenuWidget->AddToViewport();
	auto PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	UGameplayStatics::SetGamePaused(GetWorld(), true);

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;
}

void AAcmeCharacter::ChangeWalkSpeed(float amount)
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	if (!Movement) return;

	Movement->MaxWalkSpeed += amount;
}

void AAcmeCharacter::OnAttacked(int damage, ACharacterMonster* causer)
{
	if (!AnimInstance) return;
	if (IsDodgeRoll) return;

	AnimInstance->PlayAttacked();
	TakeDamage(damage, causer);
}

void AAcmeCharacter::TakeDamage(int damage, ACharacterMonster* causer)
{
	if (!StatCompoenent) return;
	if (!EquipmentComponent) return;

	//방어구 체크
	int decrease = EquipmentComponent->GetArmorDecrease();

	int finalDamage = damage - decrease;
	if (finalDamage < 0) finalDamage = 0;

	StatCompoenent->OnAttakced(finalDamage, causer);
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
	if (!QuestComponent) return false;

	bool Result = InventoryComponent->AddItem(item);
	UpdateInventoryWidget();
	QuestComponent->UpdateQuestState();

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

void AAcmeCharacter::SubmitItem(FItem item)
{
	if (!InventoryComponent) return;

	OnRewardQuest.Broadcast();

	InventoryComponent->SubmitItem(item);
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

void AAcmeCharacter::SetQuickSlots(TArray<FItem> items)
{
	if (!InventoryComponent) return;

	CurrentQuickSlotIdx = 0;

	for (int i = 0; i < items.Num(); i++)
	{
		SetQuickSlot(items[i], i);
	}
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
	
	if (EquipmentComponent->GetCurrentHand() != nullptr)
	{
		AnimInstance->PlayEquip();
	}
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
