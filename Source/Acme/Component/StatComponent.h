// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Acme/Utils/GlobalEnum.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FChangeHP, int, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FChangeST, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FChangeStamina, int);
DECLARE_MULTICAST_DELEGATE(FCoolDown);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACME_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	int GetCurrentHP() { return CurrentHP; };

	UFUNCTION()
	int GetMaxHP() { return MaxHP; };

	UFUNCTION()
	int GetCurrentST() { return CurrentSatiety; };

	UFUNCTION()
	int GetCurrentStamina() { return CurrentStamina; };

	UFUNCTION()
	void SetCurrentHP(int HP);

	UFUNCTION()
	void SetCurrentST(int ST);

	UFUNCTION()
	void SetCurrentStamina(int Stamina);

	UFUNCTION()
	void OnAttakced(int damage);

	UFUNCTION()
	void OnConsumeSatiety(int amount);

	UFUNCTION()
	void ConsumeStamina(int amount);

	UFUNCTION()
	void RecoveryStamina(int amount);

	UFUNCTION()
	void StartSprint();
	
	UFUNCTION()
	void EndSprint();

	UFUNCTION()
	void AddSatiety(int amount);

	UFUNCTION()
	void Heal(int amount);

	FCoolDown CDSkill;

	FChangeHP OnChangedHP;
	FChangeST OnChangedST;
	FChangeStamina OnChangedStamina;

private:
	UPROPERTY()
	FTimerHandle TimerDash;

	UPROPERTY()
	FTimerHandle TimerSkill;

	UPROPERTY()
	FTimerHandle TimerSatiety;

	UPROPERTY()
	FTimerHandle TimerSprint;

	UPROPERTY()
	FTimerHandle StaminaRecoveryTimer;

	//stat
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int Strength;

	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int Dexterity;

	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int Intelligence;

	//Health
	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int CurrentHP;

	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int MaxHP;

	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int CurrentStamina;

	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int MaxStamina;

	//Æ÷¸¸°¨
	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int CurrentSatiety;

	//Others
	UPROPERTY(EditAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float CoolTimedash;

	UPROPERTY(EditAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float ConsumeTimeSatiety;

	UPROPERTY(EditAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int ConsumeAmountSatiety;

	UPROPERTY(EditAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float RecoveryTime;
};
