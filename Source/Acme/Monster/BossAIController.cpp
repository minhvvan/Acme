// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/BossAIController.h"
#include "Acme/Utils/Util.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ABossAIController::ABossAIController()
{
	ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("/Script/AIModule.BlackboardData'/Game/Acme/Boss/BB_Boss.BB_Boss'"));
	if (BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}

	ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Acme/Boss/BT_Boss.BT_Boss'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
}

void ABossAIController::OnPossess(APawn* InPawn)
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

void ABossAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
