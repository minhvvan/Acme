// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/BTTaskSetAttackType.h"
#include "Acme/Monster/BossMonster.h"
#include "Acme/Monster/BossAIController.h"
#include "Acme/AcmeCharacter.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Acme/Utils/Util.h"
#include "Acme/AcmeGameInstance.h"

EBTNodeResult::Type UBTTaskSetAttackType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAcmeCharacter* Target = Cast<AAcmeCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	ABossMonster* Boss = Cast<ABossMonster>(OwnerComp.GetAIOwner()->GetPawn());

	float dist = Boss->GetDistanceTo(Target);

	if (dist <= Near)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("AttackType")), 0);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("AttackType")), 1);
	}

	DrawDebugSphere(GetWorld(), Boss->GetActorLocation(), Near, 32, FColor::Blue, false, 5.f, 0, 1.f);

	return Result;
}
