// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Hud.h"
#include "Widget_Crosshair.h"
#include "Components/Border.h"

void UWidget_Hud::SetPercent(float percent)
{
	if (Crosshair)
	{
		Crosshair->SetPercent(percent);
	}
}

void UWidget_Hud::SetCrosshairColor(FColor color)
{
	if (Crosshair)
	{
		Crosshair->SetColor(color);
	}
}

void UWidget_Hud::SetVisibleActionBorder(bool bVisible)
{
	if (bVisible) Border_Action->SetVisibility(ESlateVisibility::Visible);
	else Border_Action->SetVisibility(ESlateVisibility::Hidden);
}
