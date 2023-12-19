// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GlobalEnum.h"
#include "AC_Stat.generated.h"

DECLARE_MULTICAST_DELEGATE(FCoolDown);
DECLARE_MULTICAST_DELEGATE_TwoParams(FChangeHP, int, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FChangeST, int);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACME_API UAC_Stat : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_Stat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void ExeDash();

	UFUNCTION()
	int GetCurrentHP() { return CurrentHP; };

	UFUNCTION()
	int GetMaxHP() { return MaxHP; };

	UFUNCTION()
	int GetCurrentST() { return CurrentSatiety; };

	UFUNCTION()
	void SetCurrentHP(int HP);

	UFUNCTION()
	void SetCurrentST(int ST);

	UFUNCTION()
	void OnAttakced(int damage);

	UFUNCTION()
	void OnConsumeSatiety(int amount);

	FCoolDown CDDash;
	FCoolDown CDSkill;

	FChangeHP OnChangedHP;
	FChangeST OnChangedST;

private:
	FTimerHandle TimerDash;
	FTimerHandle TimerSkill;
	FTimerHandle TimerSatiety;


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

	//Æ÷¸¸°¨
	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int CurrentSatiety;

	//Element
	TMap<EElement, int> Elements;

	//Others
	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float CoolTimedash;

	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float ConsumeTimeSatiety;

	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int ConsumeAmountSatiety;
};