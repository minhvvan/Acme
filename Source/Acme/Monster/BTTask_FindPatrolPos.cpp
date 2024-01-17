// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/BTTask_FindPatrolPos.h"
#include "BTTask_FindPatrolPos.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/Monster/MonsterAIController.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Acme/Utils/Util.h"


UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACharacterMonster* Monster = Cast<ACharacterMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Monster) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (!NavSystem) return EBTNodeResult::Failed;


	FNavLocation RandLoc;
	if (NavSystem->GetRandomPointInNavigableRadius(Monster->GetActorLocation(), 500.f, RandLoc))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")), RandLoc.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	//return Result;
}
