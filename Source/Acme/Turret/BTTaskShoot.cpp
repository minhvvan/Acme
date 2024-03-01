// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Turret/BTTaskShoot.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/Turret/Turret.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Acme/Monster/MonsterAIController.h"
#include "Acme/AcmeCharacter.h"
#include "Sound/SoundBase.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTaskShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ATurret* Turret = Cast<ATurret>(OwnerComp.GetAIOwner()->GetPawn());
	if(!Turret) return EBTNodeResult::Failed;

	ACharacterMonster* Target = Cast<ACharacterMonster>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (!Target) return EBTNodeResult::Failed;

	Turret->SetTarget(Target);
	for (int i = 0; i < ShootNum; i++)
	{
		Turret->Fire();
	}

	DrawDebugSphere(GetWorld(), Turret->GetActorLocation(), 1000, 10, FColor::Blue);

	return result;
}
