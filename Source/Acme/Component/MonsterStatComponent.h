// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FChangeHP, int, int);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACME_API UMonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int CurrentHP;

	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int MaxHP;

	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int Strength;

	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

public:
	UFUNCTION()
	int GetCurrentHP();

	UFUNCTION()
	void SetMaxHP(int HP);

	UFUNCTION()
	int GetMaxHP();

	UFUNCTION()
	void SetCurrentHP(int HP);

	UFUNCTION()
	int GetStrength();

	UFUNCTION()
	float GetWalkSpeed();

	UFUNCTION()
	void SetStrength(int power);	


public:
	FChangeHP OnChangedHP;

};
