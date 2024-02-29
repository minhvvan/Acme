// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TurretAIController.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API ATurretAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATurretAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY()
	class UBlackboardData* BlackboardData;

	UPROPERTY()
	class UBehaviorTree* BehaviorTree;
};
