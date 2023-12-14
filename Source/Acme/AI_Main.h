// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_Main.generated.h"

UCLASS()
class ACME_API UAI_Main : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AMAttack;

public:
	UFUNCTION()
	void PlayAttack();
};
