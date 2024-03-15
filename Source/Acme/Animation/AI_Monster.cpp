// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Monster.h"

void UAI_Monster::PlayDeath()
{
	if (!Montage_IsPlaying(AMDeath)) Montage_Play(AMDeath);
}

void UAI_Monster::PlayAttack()
{
	if (!Montage_IsPlaying(AMAttack)) Montage_Play(AMAttack);
	Montage_JumpToSection(GetAttackMontageName(FMath::Rand()%2 + 1), AMAttack);
}

void UAI_Monster::PlayAttacked()
{
	if (!Montage_IsPlaying(AMAttakced)) Montage_Play(AMAttakced);
}

void UAI_Monster::AnimNotify_AttackCheck()
{
	OnAttack.Broadcast();
}

FName UAI_Monster::GetAttackMontageName(int idx)
{
	return FName(FString::Printf(TEXT("Attack%d"), idx));
}