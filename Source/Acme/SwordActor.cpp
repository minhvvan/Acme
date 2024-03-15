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