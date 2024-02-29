// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Turret/BTTaskSearchTarget.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Turret/TurretAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Debug/DebugDrawComponent.h"


UBTTaskSearchTarget::UBTTaskSearchTarget()
{
}

EBTNodeResult::Type UBTTaskSearchTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	DrawDebugSphere(GetWorld(), CurrentPawn->GetActorLocation(), Radius, 20, FColor::Blue, false, 10.f);

	return result;
}

void UBTTaskSearchTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);
	
	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		CurrentPawn->GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_Visibility,
		FCollisionShape::MakeSphere(Radius),
		QueryParams
	);


	if (bResult)
	{
		for (FOverlapResult result : OverlapResults)
		{
			ACharacterMonster* Monster = Cast<ACharacterMonster>(result.GetActor());
			if (!Monster) continue;

			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), Monster);
			return;
		}
	} 
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
	}
}
