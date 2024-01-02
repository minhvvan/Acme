// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "AcmeCharacter.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/ScaleBox.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryInnerWidget.h"
#include "Util.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;
	SetKeyboardFocus();

	Idx = 0;

	BtnLeft->OnHovered.AddDynamic(this, &UInventoryWidget::OnLeftHoverd);
	BtnLeft->OnUnhovered.AddDynamic(this, &UInventoryWidget::OnLeftLeaved);
	BtnLeft->OnClicked.AddDynamic(this, &UInventoryWidget::OnLeftClicked);

	BtnRight->OnHovered.AddDynamic(this, &UInventoryWidget::OnRightHoverd);	
	BtnRight->OnUnhovered.AddDynamic(this, &UInventoryWidget::OnRightLeaved);
	BtnRight->OnClicked.AddDynamic(this, &UInventoryWidget::OnRightClicked);

	ChangeCurrentView(0);
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Tab)
	{
		AAcmeCharacter* Character = GetOwningPlayerPawn<AAcmeCharacter>();
		Character->CloseInventory();
	}

	if (InKeyEvent.GetKey() == EKeys::Left)
	{
		OnLeftClicked();
	}

	if (InKeyEvent.GetKey() == EKeys::Right)
	{
		OnRightClicked();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UInventoryWidget::OnLeftHoverd()
{
	if (!LeftHoverAnim) return;

	PlayAnimation(LeftHoverAnim);
}

void UInventoryWidget::OnRightHoverd()
{
	if (!RightHoverAnim) return;

	PlayAnimation(RightHoverAnim);
}

void UInventoryWidget::OnLeftLeaved()
{
	if (!LeftHoverAnim) return;

	PlayAnimationReverse(LeftHoverAnim);
}

void UInventoryWidget::OnRightLeaved()
{
	if (!RightHoverAnim) return;

	PlayAnimationReverse(RightHoverAnim);
}

void UInventoryWidget::OnLeftClicked()
{
	ChangeCurrentView(-1);
}

void UInventoryWidget::OnRightClicked()
{
	ChangeCurrentView(1);
}

void UInventoryWidget::ChangeCurrentView(int change)
{
	//TODO: Idx
	UImage* CurrentImage = Cast<UImage>(Cast<UScaleBox>(HBCategory->GetChildAt(Idx))->GetChildAt(0));
	CurrentImage->SetColorAndOpacity(FLinearColor(.2f, .2f, .2f, .2f));

	Idx += change;

	if (Idx < 0) Idx = 0;
	if (Idx > 5) Idx = 5;

	UImage* NextImage = Cast<UImage>(Cast<UScaleBox>(HBCategory->GetChildAt(Idx))->GetChildAt(0));
	NextImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 1.f));

	WSInven->SetActiveWidgetIndex(Idx);
	auto InnerWidget = Cast<UInventoryInnerWidget>(WSInven->GetWidgetAtIndex(Idx));
	
	if (!InnerWidget) return;
	InnerWidget->UpdateInfo();
}