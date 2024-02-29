// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Turret/BTTaskShoot.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/Turret/Turret.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Acme/Monster/MonsterAIController.h"
#include "Sound/SoundBase.h"

EBTNodeResult::Type UBTTaskShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ATurret* Turret = Cast<ATurret>(OwnerComp.GetAIOwner()->GetPawn());
	if(!Turret) return EBTNodeResult::Failed;
	FVector CenterPos = Turret->GetActorLocation();

	ACharacterMonster* Target = Cast<ACharacterMonster>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (!Target) return EBTNodeResult::Failed;

	for (int i = 0; i < ShootNum; i++)
	{
		Turret->PlayFireSFX();

		FRotator Rot = (Target->GetActorLocation() - CenterPos).Rotation();
		Rot.Pitch = 0;
		Rot.Roll = 0;

		FQuat quat = Rot.Quaternion();
		Turret->SetActorRotation(quat);

		Target->TakeDamage(Damage);
	}


	return result;
}
