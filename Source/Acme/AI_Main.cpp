// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Main.h"
#include "Animation/AnimMontage.h"
#include "Util.h"

void UAI_Main::PlayAttack(int idx)
{
	if (!Montage_IsPlaying(AMAttack)) Montage_Play(AMAttack);
	Montage_JumpToSection(GetAttackMontageName(idx), AMAttack);
}

void UAI_Main::PlayEquip()
{
	if (!Montage_IsPlaying(AMEquip))
	{
		Montage_Play(AMEquip);
	}
}

void UAI_Main::PlayDisMantle()
{
	if (!Montage_IsPlaying(AMDismantle))
	{
		Montage_Play(AMDismantle);
	}
}

FName UAI_Main::GetAttackMontageName(int idx)
{
	return FName(FString::Printf(TEXT("Attack%d"), idx));
}

void UAI_Main::AnimNotify_AttachHand()
{
	OnEquip.Broadcast();
}

void UAI_Main::AnimNotify_AttachBack()
{
	OnDismantle.Broadcast();
}