// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalContainer.h"
#include "AcmeCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAcceptQuest, int);
DECLARE_MULTICAST_DELEGATE(FOnRewardQuest);

UCLASS(config=Game)
class AAcmeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* UICameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* UISceneCapture;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DodgeRollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpDashAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Slot1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Slot2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Slot3Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Slot4Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Slot5Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Slot6Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Slot7Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Slot8Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TabAction;

	//stat comp
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UStatComponent* StatCompoenent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	class UEquipmentComponent* EquipmentComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest, meta = (AllowPrivateAccess = "true"))
	class UQuestComponent* QuestComponent;

public:
	AAcmeCharacter();

protected:
	/** Called for movement input */
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	UFUNCTION()
	void Look(const FInputActionValue& Value);

	/** Called for Jump input */
	virtual void Jump();

	/** Called for Crouch input */
	UFUNCTION()
	void StartCrouch();

	UFUNCTION()
	void StopCrouch();

	/** Called for Dash input */
	UFUNCTION()
	void StartDodgeRoll();

	UFUNCTION()
	void StopDodgeRoll();

	UFUNCTION()
	void StartActive();	

	UFUNCTION()
	void AnimEnd(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void StartJampDashAttack();

	UFUNCTION()
	void StartSkill();

	UFUNCTION()
	void StartInteract();	
	
	UFUNCTION()
	void StartSwordAttack();
	
	UFUNCTION()
	void EndSwordAttack();

	UFUNCTION()
	void StartSprint();

	UFUNCTION()
	void EndSprint();
	
	UFUNCTION()
	void Interact();

	UFUNCTION()
	void StaminaCheck(int Stamina);

	UFUNCTION()
	void OpenInventory();

	UFUNCTION()
	void QuickSlot1Start();

	UFUNCTION()
	void QuickSlot2Start();

	UFUNCTION()
	void QuickSlot3Start();

	UFUNCTION()
	void QuickSlot4Start();

	UFUNCTION()
	void QuickSlot5Start();

	UFUNCTION()
	void QuickSlot6Start();

	UFUNCTION()
	void QuickSlot7Start();

	UFUNCTION()
	void QuickSlot8Start();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	float TurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	float DodgeForward;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	float DodgeRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool IsSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool IsCrouch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool IsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool CanAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool IsDodgeRoll;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	EAnimState AnimState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	bool IsOpenInven;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Achemy, meta = (AllowPrivateAccess = "true"))
	bool IsOpenInteractWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	int CurrentQuickSlotIdx;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element, meta = (AllowPrivateAccess = "true"))
	TArray<struct FRecipe> OwnRecipes;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HudClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UWidget_Hud* Hud;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> InventoryClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UAI_Main* AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UAlchemicComposeWidget* InteractWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UDialogueWidget> DialogueWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UDialogueWidget* DialogueWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class URewardDialogueWidget> RewardWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	URewardDialogueWidget* RewardWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UQuestNotCompleteWidget> NotCompleteWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UQuestNotCompleteWidget* NotCompleteWidget;

public:
	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool flag) { IsAttacking = flag; };

	UFUNCTION()
	void ChangeWalkSpeed(float amount);

	UFUNCTION()
	void OnAttacked(int damage);

	UFUNCTION()
	void TakeDamage(int damage);

	UFUNCTION()
	void SetAnimState(EAnimState newAnimState);

	UFUNCTION()
	void CloseInventory();
	
	UFUNCTION()
	FItemList& GetItems(EItemCategory category);

	UFUNCTION()
	FItem GetItem(EItemCategory category, int idx);

	UFUNCTION()
	bool AddItem(FItem item);

	UFUNCTION()
	void AddToInvenByIdx(FItem item, int idx);

	UFUNCTION()
	void SwapInvenByIdx(FItem fromItem, int from, int to);

	UFUNCTION()
	void SwapQuickByIdx(FItem fromItem, int from, int to);

	UFUNCTION()
	void SwapQuickAndInven(FItem item, int quickIdx, int invenIdx);

	UFUNCTION()
	void UseItem(EItemCategory Category, int idx, int amount);

	UFUNCTION()
	void SubmitItem(FItem item);

	UFUNCTION()
	void RemoveItem(EItemCategory Category, int idx);

	UFUNCTION()
	void UpdateInventoryWidget();

	UFUNCTION()
	TArray<FItem> GetQuickSlots();

	UFUNCTION()
	void SetQuickSlot(FItem item, int idx);

	UFUNCTION()
	void RemoveQuickSlot(int idx);

	UFUNCTION()
	void ChangeQuickSlotIdx(int idx);

	UFUNCTION()
	void DumpItem(EItemCategory Category, int idx);

	UFUNCTION()
	void SetIsOpenWidget(bool bOpen);

	UFUNCTION()
	void CloseInteractWidget();

	UFUNCTION()
	void SetInteractWidget(class UAlchemicComposeWidget* widget);

	UFUNCTION()
	void ConsumeStamina(int amount);

	UFUNCTION()
	void PlaySwordAttack(int idx);

	UFUNCTION()
	void Equip(EEquipmentPart part, FItem item);

	UFUNCTION()
	void UnEquip(EEquipmentPart part);

	UFUNCTION()
	void SetShowInvenCam(UPrimitiveComponent* newMesh);

	UFUNCTION()
	bool IsCompleteQuest(struct FQuest quest);

	UFUNCTION()
	void ShowDialogWidget(FQuest quest);	
	
	UFUNCTION()
	void ShowRewardWidget(FQuest quest);

	UFUNCTION()
	void ShowNotComleteWidget(FQuest quest);

	UFUNCTION()
	void AddQuest(FQuest quest);

	UFUNCTION()
	TArray<FRecipe> GetRecipes();

	UFUNCTION()
	void AddRecipe(FRecipe newRecipe);

	UFUNCTION()
	int GetItemNums(FItem item);
		 
public:
	FOnAcceptQuest OnAcceptQuest;
	FOnRewardQuest OnRewardQuest;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds);

	virtual void PostInitializeComponents();
};

