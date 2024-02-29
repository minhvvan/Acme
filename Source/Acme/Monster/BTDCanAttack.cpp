// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/BTDCanAttack.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Monster/MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTDCanAttack::UBTDCanAttack()
{
	NodeName = TEXT("CanAttack");

	AttackDistance = 200.f;
}

bool UBTDCanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	//ACharacterMonster* Monster = Cast<ACharacterMonster>(OwnerComp.GetAIOwner()->GetPawn());
	APawn* Monster = OwnerComp.GetAIOwner()->GetPawn();
	if (!Monster) return false;

	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (!Player) return false;

	return Result && Player->GetDistanceTo(Monster) <= AttackDistance;
}