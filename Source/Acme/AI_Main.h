// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_Main.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEquip);
DECLARE_MULTICAST_DELEGATE(FOnDismantle);

UCLASS()
class ACME_API UAI_Main : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMAttack;

	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMEquip;

	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMDismantle;

public:
	UFUNCTION()
	void PlayAttack(int idx);

	UFUNCTION()
	void PlayEquip();

	UFUNCTION()
	void PlayDisMantle();

	UFUNCTION()
	FName GetAttackMontageName(int idx);

	FOnEquip OnEquip;
	FOnDismantle OnDismantle;

private:
	UFUNCTION()
	void AnimNotify_AttachHand();

	UFUNCTION()
	void AnimNotify_AttachBack();
};
