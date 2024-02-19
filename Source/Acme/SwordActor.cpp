// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordActor.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/Utils/Util.h"

ASwordActor::ASwordActor()
{
	WeaponTopName = FName(TEXT("WeaponTop"));
	WeaponEndName = FName(TEXT("WeaponEnd"));
}

void ASwordActor::Active()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	if (IsCombo)
	{
		//combo
		if (ComboIdx == 2) return;

		ComboIdx++;
		AttackQueue.Enqueue(ComboIdx);

		return;
	}

	IsCombo = true;

	AttackQueue.Enqueue(ComboIdx);
	FlushQueue();
}

void ASwordActor::FlushQueue()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	if (!AttackQueue.IsEmpty())
	{
		int idx = *AttackQueue.Peek();
		AttackQueue.Pop();

		Player->PlaySwordAttack(idx);
	}
}

FVector ASwordActor::GetWeponTopPos()
{
	return Mesh->GetSocketLocation(WeaponTopName);
}

FVector ASwordActor::GetWeponEndPos()
{
	return Mesh->GetSocketLocation(WeaponEndName);
}

void ASwordActor::PlayCombo()
{
	if (!AttackQueue.IsEmpty())
	{
		FlushQueue();
	}
	else
	{
		IsCombo = false;
		ComboIdx = 0;
	}
}

void ASwordActor::BeginSeinsing()
{
	GetWorldTimerManager().SetTimer(OUT AttackTimer, this, &ASwordActor::DamageToVictim, .01f, true);
}

void ASwordActor::EndSeinsing()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());
	GetWorldTimerManager().ClearTimer(AttackTimer);

	for (AActor* Victim : VictimSet)
	{
		//Damage 계산(Victim쪽에서)
		auto Monster = Cast<ACharacterMonster>(Victim);
		if (!Monster) continue;

		Monster->SetTarget(Player);
		Monster->OnAttacked(10, Element);
	}

	VictimSet.Empty();
}

void ASwordActor::DamageToVictim()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Query;

	Query.AddIgnoredActor(this);

	FVector StartPos = GetWeponTopPos();
	FVector EndPos = GetWeponEndPos();

	if (GetWorld()->SweepMultiByChannel(HitResults, StartPos, EndPos, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(12), Query))
	{
		for (auto Result : HitResults)
		{
			AActor* Victim = Result.GetActor();

			VictimSet.Add(Victim);
		}
	}
}
