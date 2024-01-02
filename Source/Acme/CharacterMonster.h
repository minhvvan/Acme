// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GlobalEnum.h"
#include "CharacterMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDie);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UAI_Monster* AnimInstance;

	UPROPERTY(VisibleAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AAcmeCharacter> TargetCharacter;

	UPROPERTY(EditAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AInteractiveItem> ItemClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void InitState();

	UFUNCTION()
	void Die();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnAttacked(int damage, EElement ElementType);

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

	FOnDie OnDied;

	UFUNCTION()
	void SetTarget(AAcmeCharacter* target);

protected:
	UPROPERTY(VisibleAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool IsCombat;

	UPROPERTY(EditAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float CombatSustainTime;

	FTimerHandle CombatTimer;
	FTimerHandle ElementTimer;

	UFUNCTION()
	void TakeDamage(int damage);

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
