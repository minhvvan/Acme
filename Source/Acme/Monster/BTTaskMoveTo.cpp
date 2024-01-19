// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/BTTaskMoveTo.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Monster/MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskMoveTo::UBTTaskMoveTo()
{
	NodeName = TEXT("CustomMoveTo");
}

EBTNodeResult::Type UBTTaskMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACharacterMonster* Monster = Cast<ACharacterMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Monster) return EBTNodeResult::Failed;
	Monster->SetIsMoving(true);

	return Result;
}

void UBTTaskMoveTo::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	ACharacterMonster* Monster = Cast<ACharacterMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Monster) return;

	Monster->SetIsMoving(false);
}
