// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/GuideWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/WidgetSwitcher.h"
#include "Acme/Utils/Util.h"

void UGuideWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BtnOk->OnClicked.AddDynamic(this, &UGuideWidget::OnOKClicked);
	BtnLeft->OnClicked.AddDynamic(this, &UGuideWidget::OnLeftClicked);
	BtnRight->OnClicked.AddDynamic(this, &UGuideWidget::OnRightClicked);

	CurrentIdx = 0;
}

void UGuideWidget::OnOKClicked()
{
	GetOwningPlayer()->SetShowMouseCursor(false);

	ECheckBoxState State = CBOpenNext->GetCheckedState();
	if (State == ECheckBoxState::Checked)
	{
		AAcmeCharacter* Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
		if (Player) Player->SetbOpenGuide(false);
	}

	GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	RemoveFromParent();
}

void UGuideWidget::OnLeftClicked()
{
	CurrentIdx--;
	if (CurrentIdx < 0) CurrentIdx = 0;

	SwitchGuide->SetActiveWidgetIndex(CurrentIdx);
}

void UGuideWidget::OnRightClicked()
{
	CurrentIdx++;
	if (CurrentIdx >= 3) CurrentIdx = 2;

	SwitchGuide->SetActiveWidgetIndex(CurrentIdx);
}
