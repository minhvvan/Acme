// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Turret/TurretAIController.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ATurretAIController::ATurretAIController()
{
	ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("/Script/AIModule.BlackboardData'/Game/Acme/Turret/BB_Turret.BB_Turret'"));
	if (BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}

	ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Acme/Turret/BT_Turret.BT_Turret'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
}

void ATurretAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BlackboardData, BlackboardComp))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
		}
	}

}

void ATurretAIController::OnUnPossess()
{
	Super::OnUnPossess();

}
