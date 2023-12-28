// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Hud.h"
#include "Widget_Crosshair.h"
#include "Widget_Element.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "StatComponent.h"
#include "Util.h"

void UWidget_Hud::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Element_1->SetElementImage(EElement::E_Fire);
	Element_1->SetKeyImage(1);
	Element_1->SetTxtNum(0);

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

void UWidget_Hud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	float CurrentHPPercent = PB_Health->GetPercent();
	if (TargetHPPercent != CurrentHPPercent)
	{
		//interpolate
		float newPercent = FMath::Lerp(CurrentHPPercent, TargetHPPercent, .1);
		PB_Health->SetPercent(newPercent);
	}

	float CurrentSTPercent = PB_Satiety->GetPercent();
	if (TargetSTPercent != CurrentSTPercent)
	{
		//interpolate
		float newPercent = FMath::Lerp(CurrentSTPercent, TargetSTPercent, .1);
		PB_Satiety->SetPercent(newPercent);
	}

	if (TargetStaminaPercent != CurrentStaminaPercent)
	{
		//interpolate
		float newPercent = FMath::Lerp(CurrentStaminaPercent, TargetStaminaPercent, .1);
		Crosshair->SetPercent(newPercent);
		CurrentStaminaPercent = newPercent;
	}
}

void UWidget_Hud::SetVisibleActionBorder(bool bVisible)
{
	if (bVisible) Border_Action->SetVisibility(ESlateVisibility::Visible);
	else Border_Action->SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_Hud::SetHealth(int CurrentHP, int MaxHP)
{
	if (!PB_Health || !TxtCurrentHealth || !TxtMaxHealth) return;

	float percentage = float(CurrentHP) / MaxHP;

	TargetHPPercent = percentage;
	TxtCurrentHealth->SetText(FText::AsNumber(CurrentHP));
	TxtMaxHealth->SetText(FText::AsNumber(MaxHP));
}

void UWidget_Hud::SetSatiety(int CurrentST)
{
	if (!PB_Satiety || !TxtCurrentSatiety) return;

	float percentage = float(CurrentST) / 100;

	TargetSTPercent = percentage;
	TxtCurrentSatiety->SetText(FText::AsNumber(CurrentST));
}

void UWidget_Hud::SetStamina(int CurrentStamina)
{
	if (!Crosshair) return;

	float percentage = float(CurrentStamina) / 100;
	TargetStaminaPercent = percentage;
}

void UWidget_Hud::ChangeElement(EElement element, int amount)
{
	//1234중 하나에 있다면 change

	if (Element_1->GetCurrentElement() == element)
	{
		Element_1->SetTxtNum(Element_1->GetTxtNum() + 1);
	}

	if (Element_2->GetCurrentElement() == element)
	{
		Element_2->SetTxtNum(Element_2->GetTxtNum() + 1);
	}

	if (Element_3->GetCurrentElement() == element)
	{
		Element_3->SetTxtNum(Element_3->GetTxtNum() + 1);
	}

	if (Element_4->GetCurrentElement() == element)
	{
		Element_4->SetTxtNum(Element_4->GetTxtNum() + 1);
	}
}

void UWidget_Hud::BindStatus(UStatComponent* StatComp)
{
	StatComp->OnChangedHP.AddUObject(this, &UWidget_Hud::SetHealth);
	StatComp->OnChangedST.AddUObject(this, &UWidget_Hud::SetSatiety);
	StatComp->OnChangedStamina.AddUObject(this, &UWidget_Hud::SetStamina);
	StatComp->OnChangedElements.AddUObject(this, &UWidget_Hud::ChangeElement);
}
