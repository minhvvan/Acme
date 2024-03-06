// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/BossAnimInstance.h"

void UBossAnimInstance::PlayBite()
{
	if (!Montage_IsPlaying(AMBite)) Montage_Play(AMBite);
}

void UBossAnimInstance::PlayFire()
{
	if (!Montage_IsPlaying(AMFire)) Montage_Play(AMFire);
}

void UBossAnimInstance::PlayFlyFire()
{
	if (!Montage_IsPlaying(AMFlyFire)) Montage_Play(AMFlyFire);
}

void UBossAnimInstance::PlayTailAttack()
{
	if (!Montage_IsPlaying(AMTailAttack)) Montage_Play(AMTailAttack);
}

void UBossAnimInstance::AnimNotify_BiteAttack()
{
	OnBite.Broadcast();
}

void UBossAnimInstance::AnimNotify_FireAttack()
{
	OnFire.Broadcast();
}
