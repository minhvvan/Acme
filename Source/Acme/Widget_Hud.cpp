// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Hud.h"
#include "Widget_Crosshair.h"
#include "Widget_Element.h"
#include "Components/Border.h"

void UWidget_Hud::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Element_2->SetElementImage(EElement::E_Water);
	Element_2->SetKeyImage(2);
	Element_2->SetTxtNum(0);

	Element_3->SetElementImage(EElement::E_Earth);
	Element_3->SetKeyImage(3);
	Element_3->SetTxtNum(0);

	Element_4->SetElementImage(EElement::E_Air);
	Element_4->SetKeyImage(4);
	Element_4->SetTxtNum(0);
}

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
