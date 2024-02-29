// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskSearchTarget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UBTTaskSearchTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskSearchTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float Radius;
};
