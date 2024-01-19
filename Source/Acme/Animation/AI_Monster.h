// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_Monster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttack);

UCLASS()
class ACME_API UAI_Monster : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMDeath;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMAttack;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMAttakced;

public:
	UFUNCTION()
	void PlayDeath();

	UFUNCTION()
	void PlayAttack();

	UFUNCTION()
	void PlayAttacked();

	UFUNCTION()
	void AnimNotify_AttackCheck();

public:
	FOnAttack OnAttack;
};
