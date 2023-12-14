// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Main.h"
#include "Animation/AnimMontage.h"
#include "Util.h"

void UAI_Main::PlayAttack()
{
	if (!Montage_IsPlaying(AMAttack))
	{
		Montage_Play(AMAttack);
	}
}
