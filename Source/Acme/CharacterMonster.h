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

protected:
	UPROPERTY(VisibleAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool IsCombat;

	UPROPERTY(EditAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float CombatSustainTime;

	FTimerHandle CombatTimer;

	UPROPERTY(VisibleAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TArray<EElement> Elements;

	//! --------------------- Element Reactions
	CallBackFunction ElementReactions[7][7];

	UFUNCTION()
	void ElementReaction(EElement element);

	UFUNCTION()
	bool FlushElements();

	//Fire
	UFUNCTION()
	void Evaporation();

	UFUNCTION()
	void Combustion();

	UFUNCTION()
	void Melting();

	UFUNCTION()
	void Spread();

	//Water
	UFUNCTION()
	void Frozen();

	UFUNCTION()
	void Stunned();

	//Earth
	UFUNCTION()
	void Weathered();

	UFUNCTION()
	void Swamp();	
	

	//! --------------------- CC
	UFUNCTION()
	void OnFrozen();

	UFUNCTION()
	void OnElectricShock();
};
