// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/MonsterAIController.h"
#include "Acme/Utils/Util.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterAIController::AMonsterAIController()
{
	ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("/Script/AIModule.BlackboardData'/Game/Goblin/AI/BB_Monster.BB_Monster'"));
	if (BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}

	ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Goblin/AI/BT_Monster.BT_Monster'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BlackboardData, BlackboardComp))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			UUtil::DebugPrint("RunBT");
		}
	}

}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();

}
