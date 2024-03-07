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
	MouthOffset.Set(100.f, 100.f, 0.f);

	bShouldMove = false;
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
	BossAnimInstance->OnFire.AddUObject(this, &ABossMonster::FireBall);
	BossAnimInstance->OnTail.AddUObject(this, &ABossMonster::TailAttackCheck);
	BossAnimInstance->OnMontageEnded.AddDynamic(this, &ABossMonster::OnMontageEnded);
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

	if (!bShouldMove) return;
	if (Dist <= 400.f)
	{
		bShouldMove = false;
		return;
	}

	FVector NewPos = FMath::Lerp(GetActorLocation(), TargetPos, .05f);
	Dist = FVector::Dist(TargetPos, GetActorLocation());

	SetActorLocation(NewPos);
}

void ABossMonster::OnAttacked(int damage)
{
	if (!HPBar) return;
	if (!BossAnimInstance) return;
	if (!TargetCharacter) return;
	if (!StatCompoenent) return;

	IsCombat = true;
	HPBar->SetVisibility(true);

	if (!BossAIController) BossAIController = Cast<ABossAIController>(GetController());
	BossAIController->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), TargetCharacter);

	StatCompoenent->GetCurrentHP();
	bool bUnderHalf = ((float)StatCompoenent->GetCurrentHP() / StatCompoenent->GetMaxHP()) <= .5f;
	BossAIController->GetBlackboardComponent()->SetValueAsBool(FName(TEXT("bUnderHalf")), bUnderHalf);

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

void ABossMonster::Move()
{
	bShouldMove = true;
	TargetPos = TargetCharacter->GetActorLocation();

	Dist = FVector::Dist(TargetPos, GetActorLocation());
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

	Move();

	if (CombatTimer.IsValid()) GetWorldTimerManager().ClearTimer(CombatTimer);
	GetWorldTimerManager().SetTimer(CombatTimer, this, &ABossMonster::FinishCombat, CombatSustainTime, false);
}

void ABossMonster::BiteAttackCheck()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Query;

	Query.AddIgnoredActor(this);

	FVector Center = GetMesh()->GetBoneLocation(FName(TEXT("Jaw")));
	FVector End = Center + GetActorForwardVector() * 200;
	End.Z -= 200;

	bool bHit = GetWorld()->SweepMultiByChannel(OUT HitResults, Center, End, FQuat::Identity, ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeCapsule(FVector(100,50,100)), Query);

	//DrawDebugCapsule(GetWorld(), Center, 50, 25, FQuat::Identity, FColor::Red, false, 60.f, 0, 2.f);
	//DrawDebugCapsule(GetWorld(), End, 50, 25, FQuat::Identity, FColor::Blue, false, 60.f, 0, 2.f);

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

void ABossMonster::FireBall()
{
	FActorSpawnParameters param;
	param.Instigator = this;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLoc = GetMesh()->GetBoneLocation(FName(TEXT("Jaw")));

	AFireBallProjectile* FireBall = GetWorld()->SpawnActor<AFireBallProjectile>(ProjectileClass, SpawnLoc, GetActorRotation(), param);

	FVector Dir = (TargetCharacter->GetActorLocation() - SpawnLoc);
	Dir.Normalize();

	FireBall->FireInDirection(Dir);
}

void ABossMonster::TailAttackCheck()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Query;

	Query.AddIgnoredActor(this);

	FVector Start = GetMesh()->GetBoneLocation(FName(TEXT("TailEnd")));
	FVector End = Start + GetActorRightVector() * 200;

	bool bHit = GetWorld()->SweepMultiByChannel(OUT HitResults, Start, End, FQuat::Identity, ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeCapsule(FVector(100, 50, 100)), Query);

	//DrawDebugCapsule(GetWorld(), Start, 50, 25, FQuat::Identity, FColor::Red, false, 60.f, 0, 2.f);
	//DrawDebugCapsule(GetWorld(), End, 50, 25, FQuat::Identity, FColor::Blue, false, 60.f, 0, 2.f);

	FVector LuanchDir = End - Start;
	LuanchDir.Z += 30;

	if (bHit)
	{
		for (auto Result : HitResults)
		{
			AAcmeCharacter* Player = Cast<AAcmeCharacter>(Result.GetActor());
			if (!Player) continue;

			Player->TakeDamage(StatCompoenent->GetStrength() * .3);
			Player->LaunchCharacter(LuanchDir * 15, true, true);
			return;
		}
	}
}

void ABossMonster::Die()
{
	BossAnimInstance->PlayDeathAnim();
}

void ABossMonster::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	FString MontageName = Montage->GetName();

	if (MontageName == TEXT("AM_Death"))
	{
		Destroy();
		OnDied.Broadcast();

		FVector SpawnPos = GetActorLocation();
		SpawnPos.Z += 10;

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (DropItems.IsEmpty()) return;
		int idx = FMath::RandRange(0, DropItems.Num() - 1);
		if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

		FItem temp = GameInstance->GetItemInfo(DropItems[idx]);

		AInteractiveItem* DropItem = GetWorld()->SpawnActor<AInteractiveItem>(DropItemClass, FTransform(FRotator::ZeroRotator, SpawnPos), SpawnParam);
		DropItem->Init(temp);
	}
}
