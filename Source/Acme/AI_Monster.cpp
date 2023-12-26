// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Monster.h"

void UAI_Monster::PlayDeath()
{
	if (!Montage_IsPlaying(AMDeath)) Montage_Play(AMDeath);
}
