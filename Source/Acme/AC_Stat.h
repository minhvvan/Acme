// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GlobalEnum.h"
#include "AC_Stat.generated.h"

DECLARE_MULTICAST_DELEGATE(FCoolDown)

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

	FCoolDown CDDash;
	FCoolDown CDSkill;

private:
	FTimerHandle TimerDash;
	FTimerHandle TimerSkill;

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

	//Element
	TMap<EElement, int> Elements;

	//Others
	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float CoolTimedash;
};