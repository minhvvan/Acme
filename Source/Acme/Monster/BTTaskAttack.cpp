// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/BTTaskAttack.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Monster/MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskAttack::UBTTaskAttack()
{
	NodeName = TEXT("Attack");

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACharacterMonster* Monster = Cast<ACharacterMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Monster) return EBTNodeResult::Failed;

	bIsAttacking = true;
	Monster->Attack();

	Monster->OnAttackEnd.AddLambda([this]() {
		bIsAttacking = false;
	});

	return Result;
}

void UBTTaskAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
