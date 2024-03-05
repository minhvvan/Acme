// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttack);

UCLASS()
class ACME_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMDeath;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMBite;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMFire;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMFlyFire;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMTailAttack;

public:
	FOnAttack OnAttack;
	FOnAttack OnBite;

	UFUNCTION()
	void PlayBite();

	UFUNCTION()
	void PlayFire();

	UFUNCTION()
	void PlayFlyFire();

	UFUNCTION()
	void PlayTailAttack();

	UFUNCTION()
	void AnimNotify_BiteAttack();
};
