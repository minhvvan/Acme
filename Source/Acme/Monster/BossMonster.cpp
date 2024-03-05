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

	CombatSustainTime = 100.f;
}

void ABossMonster::BeginPlay()
{
	ACharacter::BeginPlay();

	StatCompoenent->SetMaxHP(1000);
	StatCompoenent->SetCurrentHP(1000);
	StatCompoenent->SetStrength(30);
	InitState();

	BossAnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	BossAnimInstance->OnBite.AddUObject(this, &ABossMonster::BiteAttackCheck);
	//BossAnimInstance->OnMontageEnded.AddDynamic(this, &ABossMonster::OnMontageEnd);
}

void ABossMonster::FinishCombat()
{
	IsCombat = false;
	HPBar->SetVisibility(false);
	TargetCharacter = nullptr;
	BossAIController->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
	CombatTimer.Invalidate();
}

void ABossMonster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!TargetCharacter) return;

	FVector Dir = TargetCharacter->GetActorLocation() - GetActorLocation();
	FRotator Rot = Dir.Rotation();
	Rot.Pitch = 0;
	Rot.Roll = 0;

	SetActorRotation(Rot);
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
	GetWorldTimerManager().SetTimer(CombatTimer, this, &ABossMonster::FinishCombat, CombatSustainTime, false);

	if (AudioComp)
	{
		AudioComp->SetSound(SFXList[EMonsterState::E_Attacked]);
		AudioComp->Play();
	}

	TakeDamage(damage);
}

void ABossMonster::Fire()
{
	if (!BossAnimInstance) return;
	BossAnimInstance->PlayFire();

	if (CombatTimer.IsValid()) GetWorldTimerManager().ClearTimer(CombatTimer);
	GetWorldTimerManager().SetTimer(CombatTimer, this, &ABossMonster::FinishCombat, CombatSustainTime, false);
}

void ABossMonster::Bite()
{
	if (!BossAnimInstance) return;
	BossAnimInstance->PlayBite();

	if (CombatTimer.IsValid()) GetWorldTimerManager().ClearTimer(CombatTimer);
	GetWorldTimerManager().SetTimer(CombatTimer, this, &ABossMonster::FinishCombat, CombatSustainTime, false);
}

void ABossMonster::TailAttack()
{
	if (!BossAnimInstance) return;
	BossAnimInstance->PlayTailAttack();

	if (CombatTimer.IsValid()) GetWorldTimerManager().ClearTimer(CombatTimer);
	GetWorldTimerManager().SetTimer(CombatTimer, this, &ABossMonster::FinishCombat, CombatSustainTime, false);
}

void ABossMonster::FlyFire()
{
	if (!BossAnimInstance) return;
	BossAnimInstance->PlayFlyFire();

	if (CombatTimer.IsValid()) GetWorldTimerManager().ClearTimer(CombatTimer);
	GetWorldTimerManager().SetTimer(CombatTimer, this, &ABossMonster::FinishCombat, CombatSustainTime, false);
}

void ABossMonster::BiteAttackCheck()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Query;

	Query.AddIgnoredActor(this);

	FVector Center = GetActorLocation();
	FVector End = Center + GetActorForwardVector() * 1200;
	End.Z -= 500;

	bool bHit = GetWorld()->SweepMultiByChannel(OUT HitResults, Center, End, FQuat::Identity, ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeSphere(300), Query);

	if (bHit)
	{
		for (auto Result : HitResults)
		{
			AAcmeCharacter* Player = Cast<AAcmeCharacter>(Result.GetActor());
			if (!Player) continue;

			Player->OnAttacked(StatCompoenent->GetStrength());
			return;
		}
	}
}
