// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Turret/BTServiceSearchTarget.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/Monster/MonsterAIController.h"
#include "Acme/Turret/Turret.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Acme/Utils/Util.h"

void UBTServiceSearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	ATurret* Turret = Cast<ATurret>(OwnerComp.GetAIOwner()->GetPawn());

	if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))) != nullptr)
	{
		Turret->PlayFireFX(false);
		return;
	}

	FVector CenterPos = Turret->GetActorLocation();
	FCollisionQueryParams Query;

	TArray<FOverlapResult> OverlapResults;
	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		CenterPos,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(Radius),
		Query
	);

	if (bResult)
	{
		for (auto Result : OverlapResults)
		{
			ACharacterMonster* Monster = Cast<ACharacterMonster>(Result.GetActor());
			if (!Monster) continue;

			if (Monster->IsPendingKill())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
				Turret->PlayFireFX(false);
				return;
			}

			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), Monster);
			Turret->PlayFindEnermySFX();
			return;
		}
	}
	else
	{
		Turret->PlayFireFX(false);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
	}
}
