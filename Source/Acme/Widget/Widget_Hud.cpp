// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Hud.h"
#include "Widget_Crosshair.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Acme/Component/StatComponent.h"
#include "Acme/Widget/QuickSlotWidget.h"
#include "Acme/Utils/Util.h"
#include "Acme/AcmeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void UWidget_Hud::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
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

	if (Player)
	{
		FRotator rot = Player->GetFollowCamera()->GetComponentRotation();

		float FinalX = rot.Yaw;

		FinalX *= -1;
		FinalX *= 10;
		FinalX -= 450;

		FVector2D FinalPos = FVector2D(FinalX, 30);

		UWidgetLayoutLibrary::SlotAsCanvasSlot(ImgCompass)->SetPosition(FinalPos);
	}
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

void UWidget_Hud::SetQuickSlots(TArray<FItem> QuickSlots)
{
	if (QuickSlots.Num() != 8) return;

	WBP_QuickSlot1->SetItemInfo(QuickSlots[0]);
	WBP_QuickSlot2->SetItemInfo(QuickSlots[1]);
	WBP_QuickSlot3->SetItemInfo(QuickSlots[2]);
	WBP_QuickSlot4->SetItemInfo(QuickSlots[3]);
	WBP_QuickSlot5->SetItemInfo(QuickSlots[4]);
	WBP_QuickSlot6->SetItemInfo(QuickSlots[5]);
	WBP_QuickSlot7->SetItemInfo(QuickSlots[6]);
	WBP_QuickSlot8->SetItemInfo(QuickSlots[7]);

	QuickSlotWidgets.Add(WBP_QuickSlot1);
	QuickSlotWidgets.Add(WBP_QuickSlot2);
	QuickSlotWidgets.Add(WBP_QuickSlot3);
	QuickSlotWidgets.Add(WBP_QuickSlot4);
	QuickSlotWidgets.Add(WBP_QuickSlot5);
	QuickSlotWidgets.Add(WBP_QuickSlot6);
	QuickSlotWidgets.Add(WBP_QuickSlot7);
	QuickSlotWidgets.Add(WBP_QuickSlot8);
}

void UWidget_Hud::BindStatus(UStatComponent* StatComp)
{
	StatComp->OnChangedHP.AddUObject(this, &UWidget_Hud::SetHealth);
	StatComp->OnChangedST.AddUObject(this, &UWidget_Hud::SetSatiety);
	StatComp->OnChangedStamina.AddUObject(this, &UWidget_Hud::SetStamina);
}

void UWidget_Hud::ChangeSelectedSlot(int idx)
{
	if (QuickSlotWidgets[CurrentQuickSlotIdx])
	{
		QuickSlotWidgets[CurrentQuickSlotIdx]->SetUnSelectBorder();
	}

	CurrentQuickSlotIdx = idx;
	if (QuickSlotWidgets[CurrentQuickSlotIdx])
	{
		QuickSlotWidgets[CurrentQuickSlotIdx]->SetSelectBorder();
	}
}
