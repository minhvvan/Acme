// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Main.h"
#include "Animation/AnimMontage.h"
#include "Acme/Utils/Util.h"

void UAI_Main::PlayAttack(int idx)
{
	if (!Montage_IsPlaying(AMAttack)) Montage_Play(AMAttack);
	Montage_JumpToSection(GetAttackMontageName(idx), AMAttack);
}

void UAI_Main::PlayAttacked()
{
	if (!Montage_IsPlaying(AMAttacked)) Montage_Play(AMAttacked);
}

void UAI_Main::PlayJumpDashAttack()
{
	if (!Montage_IsPlaying(AMJDAttack)) Montage_Play(AMJDAttack);
}

void UAI_Main::PlayEquip()
{
	if (!Montage_IsPlaying(AMEquip))
	{
		Montage_Play(AMEquip);
	}
}

void UAI_Main::PlayExhaust()
{
	if (!Montage_IsPlaying(AMExhaust))
	{
		Montage_Play(AMExhaust);
	}
}

void UAI_Main::PlayInteract()
{
	if (!Montage_IsPlaying(AMInteract))
	{
		Montage_Play(AMInteract);
	}
}

void UAI_Main::PlayDodgeRoll()
{
	if (!Montage_IsPlaying(AMDodgeRoll))
	{
		Montage_Play(AMDodgeRoll);
	}
}

FName UAI_Main::GetAttackMontageName(int idx)
{
	return FName(FString::Printf(TEXT("Attack%d"), idx));
}

void UAI_Main::AnimNotify_AttackStart()
{
	OnAttackStart.Broadcast();
}

void UAI_Main::AnimNotify_AttackEnd()
{
	OnAttackEnd.Broadcast();
}

void UAI_Main::AnimNotify_Interact()
{
	OnInteract.Broadcast();
}

void UAI_Main::AnimNotify_DodgeRoll()
{
	OnDodgeRoll.Broadcast();
}
