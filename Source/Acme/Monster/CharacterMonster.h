// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Acme/Utils/GlobalEnum.h"
#include "CharacterMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDie);
DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class ACME_API ACharacterMonster : public ACharacter
{
	GENERATED_BODY()

	typedef void (ACharacterMonster::* CallBackFunction)(void);

public:
	// Sets default values for this character's properties
	ACharacterMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMonsterStatComponent> StatCompoenent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> HPBar;

	UPROPERTY(VisibleAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AAcmeCharacter> TargetCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SFX, meta = (AllowPrivateAccess = "true"))
	TMap<EMonsterState, class USoundBase*> SFXList;

	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

private:
	UPROPERTY()
	class AMonsterAIController* AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UAI_Monster* AnimInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void InitState();

	UFUNCTION()
	virtual void Die();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void OnAttacked(int damage);

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);	
	
	UFUNCTION()
	void AttackCheck();

	FOnDie OnDied;
	FOnAttackEnd OnAttackEnd;

	UFUNCTION()
	void SetTarget(AAcmeCharacter* target);

	UFUNCTION(BlueprintCallable)
	bool GetIsMoving();

	UFUNCTION()
	void SetIsMoving(bool bIsMoving);

	UFUNCTION()
	virtual void FinishCombat();

	UFUNCTION()
	AAcmeCharacter* GetTarget();

	UFUNCTION()
	void SetCenterPos(FVector pos);

	UFUNCTION()
	FVector GetCenterPos();

	UFUNCTION()
	void SetSearchRadius(float radius);

	UFUNCTION()
	float GetSearchRadius();

	UFUNCTION()
	void TakeDamage(int damage);

protected:
	UPROPERTY(VisibleAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool IsCombat;

	UPROPERTY(EditAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float CombatSustainTime;

	UPROPERTY(VisibleAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool IsMoving;

	UPROPERTY(VisibleAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float AttackRange;

	UPROPERTY(VisibleAnywhere, Category = Default, meta = (AllowPrivateAccess = "true"))
	FVector CenterPos;

	UPROPERTY(EditAnywhere, Category = Default, meta = (AllowPrivateAccess = "true"))
	float SearchRadius;

	UPROPERTY(VisibleAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool IsAttacking;

	UPROPERTY(EditAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AInteractiveItem> DropItemClass;

	UPROPERTY(EditAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	TArray<EItemName> DropItems;

	FTimerHandle CombatTimer;
	FTimerHandle ElementTimer;

	//! --------------------- CC
	UFUNCTION()
	void OnFrozen();

	UFUNCTION()
	void OnElectricShock();

	UFUNCTION()
	void OnBurn();

	UFUNCTION()
	void KnockBack(float dist);
};
