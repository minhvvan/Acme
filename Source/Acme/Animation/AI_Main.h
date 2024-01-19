// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_Main.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEquip);
DECLARE_MULTICAST_DELEGATE(FOnDismantle);
DECLARE_MULTICAST_DELEGATE(FOnAttackStart);
DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);
DECLARE_MULTICAST_DELEGATE(FOnInteract);


UCLASS()
class ACME_API UAI_Main : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMAttack;
	
	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMJDAttack;	

	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMAttacked;

	UPROPERTY(EditAnywhere, Category = "Equip", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMEquip;

	UPROPERTY(EditAnywhere, Category = "Equip", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMDismantle;	
	
	UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMExhaust;	
	
	UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMInteract;

public:
	UFUNCTION()
	void PlayAttack(int idx);

	UFUNCTION()
	void PlayAttacked();
	
	UFUNCTION()
	void PlayJumpDashAttack();

	UFUNCTION()
	void PlayEquip();

	UFUNCTION()
	void PlayDisMantle();	
	
	UFUNCTION()
	void PlayExhaust();	
	
	UFUNCTION()
	void PlayInteract();

	UFUNCTION()
	FName GetAttackMontageName(int idx);

	FOnEquip OnEquip;
	FOnDismantle OnDismantle;
	FOnAttackStart OnAttackStart;
	FOnAttackEnd OnAttackEnd;
	FOnInteract OnInteract;

private:
	UFUNCTION()
	void AnimNotify_AttachHand();

	UFUNCTION()
	void AnimNotify_AttachBack();	
	
	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_Interact();
};
