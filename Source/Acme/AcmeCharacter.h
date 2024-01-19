// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalContainer.h"
#include "AcmeCharacter.generated.h"



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
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EquipAction;

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
	void StartDash();

	UFUNCTION()
	void StopDash();

	UFUNCTION()
	void CoolDownDash();

	/** Called for Attack input */
	UFUNCTION()
	void StartAttack();	

	UFUNCTION()
	void FireAttack(/*¼¼±â*/);

	UFUNCTION()
	void EndAttack(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void StartJampDashAttack();

	UFUNCTION()
	void StartSkill();

	UFUNCTION()
	void StartInteract();	
	
	UFUNCTION()
	void ChangeEquip();

	UFUNCTION()
	void AttachWeaponToHand();

	UFUNCTION()
	void AttachWeaponToBack();			
	
	UFUNCTION()
	void AttackStart();	
	
	UFUNCTION()
	void AttackEnd();

	UFUNCTION()
	void AttackCheck();	
	
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
	float DashForward;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	float DashRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool IsDashing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool IsCrouch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool CanDash;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool IsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move, meta = (AllowPrivateAccess = "true"))
	bool CanAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	EAnimState AnimState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool IsCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int ComboIdx;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	bool IsOpenInven;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element, meta = (AllowPrivateAccess = "true"))
	EElement ActiveElement;

	UPROPERTY()
	FTimerHandle AttackTimer;

	UPROPERTY()
	FTimerHandle StaminaRecoveryTimer;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor_Projectile> ProjectileClass;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class AActorInteractive> OverlapActor;

	TQueue<int> AttackQueue;

	UPROPERTY()
	TSet<AActor*> VictimSet;

	UFUNCTION()
	void FlushQueue();

public:
	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool flag) { IsAttacking = flag; };

	UFUNCTION()
	void ShowOverlapInfo(bool bShow);

	UFUNCTION()
	void ChangeWalkSpeed(float amount);

	UFUNCTION()
	void OnAttacked(int damage);

	UFUNCTION()
	void TakeDamage(int damage);

public:
	UFUNCTION()
	void CloseInventory();
	
	UFUNCTION()
	void AddElement(EElement element);
	
	UFUNCTION()
	FItemList& GetItems(EItemCategory category);

	UFUNCTION()
	FItem GetItem(EItemCategory category, int idx);

	UFUNCTION()
	bool AddItem(FItem item);

	UFUNCTION()
	void MoveItems(EItemCategory Category, int from, int to);

	UFUNCTION()
	void UpdateInventoryWidget();

	UFUNCTION()
	TArray<FItem> GetQuickSlots();

	UFUNCTION()
	void SetQuickSlot(FItem item, int idx);

	UFUNCTION()
	void Equip(int idx);

	UFUNCTION()
	void Unequip(int idx);

	UFUNCTION()
	void SetWeapon(FItem item);

	UFUNCTION()
	void RemoveWeapon();

	UFUNCTION()
	void DumpItem(EItemCategory Category, int idx);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds);

	virtual void PostInitializeComponents();
};

