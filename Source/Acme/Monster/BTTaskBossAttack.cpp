// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/BTTaskBossAttack.h"
#include "Acme/Monster/BossMonster.h"
#include "Acme/Monster/BossAIController.h"
#include "Acme/AcmeCharacter.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Acme/Utils/Util.h"
#include "Acme/Framework/AcmeGameInstance.h"

EBTNodeResult::Type UBTTaskBossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	EAttackType AttackType = static_cast<EAttackType>(OwnerComp.GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("AttackType"))));
	
	switch (AttackType)
	{
	case EAttackType::E_Bite:
		Cast<ABossMonster>(OwnerComp.GetAIOwner()->GetPawn())->Bite();
		break;
	case EAttackType::E_Fire:
		Cast<ABossMonster>(OwnerComp.GetAIOwner()->GetPawn())->Fire();
		break;
	case EAttackType::E_Move:
		Cast<ABossMonster>(OwnerComp.GetAIOwner()->GetPawn())->Move();
		break;
	case EAttackType::E_FlyFire:
		Cast<ABossMonster>(OwnerComp.GetAIOwner()->GetPawn())->FlyFire();
		break;
	case EAttackType::E_Tail:
		Cast<ABossMonster>(OwnerComp.GetAIOwner()->GetPawn())->TailAttack();
		break;
	}

	return Result;
}
