// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/BossMonster.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Acme/Component/MonsterStatComponent.h"
#include "Acme/Widget/Widget_HPBar.h"
#include "Acme/Monster/BossAnimInstance.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Item/InteractiveItem.h"
#include "Acme/Utils/Util.h"
#include "MonsterAIController.h"
#include "Debug/DebugDrawComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Acme/AcmeGameInstance.h"
#include "Components/AudioComponent.h"
#include "Acme/Item/InteractiveItem.h"
#include "Acme/Monster/BossAIController.h"

ABossMonster::ABossMonster()
{
	AIControllerClass = ABossAIController::StaticClass();

}

void ABossMonster::BeginPlay()
{
	ACharacter::BeginPlay();

	InitState();

	BossAnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	//BossAnimInstance->OnMontageEnded.AddDynamic(this, &ABossMonster::OnMontageEnd);
	//BossAnimInstance->OnAttack.AddUObject(this, &ACharacterMonster::AttackCheck);
}

void ABossMonster::OnAttacked(int damage)
{
	if (!HPBar) return;
	if (!BossAnimInstance) return;
	if (!TargetCharacter) return;

	IsCombat = true;
	HPBar->SetVisibility(true);

	if (!BossAIController) BossAIController = Cast<ABossAIController>(GetController());
	BossAIController->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), TargetCharacter);

	if (CombatTimer.IsValid()) GetWorldTimerManager().ClearTimer(CombatTimer);
	GetWorldTimerManager().SetTimer(CombatTimer, this, &ACharacterMonster::FinishCombat, CombatSustainTime, false);

	if (AudioComp)
	{
		AudioComp->SetSound(SFXList[EMonsterState::E_Attacked]);
		AudioComp->Play();
	}

	UUtil::DebugPrint("Attacked");

	TakeDamage(damage);
}

void ABossMonster::Fire()
{
	//È­¿°±¸
	UUtil::DebugPrint("Fire");
}

void ABossMonster::Bite()
{
	UUtil::DebugPrint("Bite");
}

void ABossMonster::TailAttack()
{
	UUtil::DebugPrint("TailAttack");
}

void ABossMonster::FlyFire()
{
	UUtil::DebugPrint("FlyFire");
}
