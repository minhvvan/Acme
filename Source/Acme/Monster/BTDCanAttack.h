// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDCanAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UBTDCanAttack : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDCanAttack();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

	UPROPERTY(EditAnywhere)
	float AttackDistance;
};
