// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/ScaleBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryInnerWidget.h"
#include "Acme/Utils/Util.h"
#include "QuickSlotWidget.h"
#include "TileInventoryWidget.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Widget/EquipmentSlot.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (OpenSFX) PlaySound(OpenSFX);

	bIsFocusable = true;
	SetKeyboardFocus();

	Index = 0;

	if (!BtnLeft->OnHovered.IsBound())
	{
		BtnLeft->OnHovered.AddDynamic(this, &UInventoryWidget::OnLeftHoverd);
		BtnLeft->OnUnhovered.AddDynamic(this, &UInventoryWidget::OnLeftLeaved);
		BtnLeft->OnClicked.AddDynamic(this, &UInventoryWidget::OnLeftClicked);
	}

	if (!BtnRight->OnHovered.IsBound())
	{
		BtnRight->OnHovered.AddDynamic(this, &UInventoryWidget::OnRightHoverd);
		BtnRight->OnUnhovered.AddDynamic(this, &UInventoryWidget::OnRightLeaved);
		BtnRight->OnClicked.AddDynamic(this, &UInventoryWidget::OnRightClicked);
	}

	ClearAllCategory();
	ChangeCurrentView(0);
	SetQuickSlots();
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
	UImage* CurrentImage = Cast<UImage>(Cast<UScaleBox>(HBCategory->GetChildAt(Index))->GetChildAt(0));
	CurrentImage->SetColorAndOpacity(FLinearColor(.2f, .2f, .2f, .2f));

	Index = (Index + change + 6) % 6;

	UImage* NextImage = Cast<UImage>(Cast<UScaleBox>(HBCategory->GetChildAt(Index))->GetChildAt(0));
	NextImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 1.f));

	WSInven->SetActiveWidgetIndex(Index);
	CurrentCategoryView = Cast<UTileInventoryWidget>(WSInven->GetWidgetAtIndex(Index));
	
	if (!CurrentCategoryView) return;

	CurrentCategoryView->SetCategory((EItemCategory)Index);
	CurrentCategoryView->UpdateInfo();

	CurrentCategoryView->SetInven(this);
}

void UInventoryWidget::ClearAllCategory()
{
	for (int i = 0; i < 6; i++)
	{
		UImage* CurrentImage = Cast<UImage>(Cast<UScaleBox>(HBCategory->GetChildAt(i))->GetChildAt(0));

		if (!CurrentImage) continue;
		CurrentImage->SetColorAndOpacity(FLinearColor(.2f, .2f, .2f, .2f));
	}
}

void UInventoryWidget::SetQuickSlots()
{
	AAcmeCharacter* Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	if (!Player) return;

	auto QuickSlots = Player->GetQuickSlots();
	if (QuickSlots.Num() != 8) return;

	WBP_QuickSlot1->SetItemInfo(QuickSlots[0]);
	WBP_QuickSlot2->SetItemInfo(QuickSlots[1]);
	WBP_QuickSlot3->SetItemInfo(QuickSlots[2]);
	WBP_QuickSlot4->SetItemInfo(QuickSlots[3]);
	WBP_QuickSlot5->SetItemInfo(QuickSlots[4]);
	WBP_QuickSlot6->SetItemInfo(QuickSlots[5]);
	WBP_QuickSlot7->SetItemInfo(QuickSlots[6]);
	WBP_QuickSlot8->SetItemInfo(QuickSlots[7]);

	WBP_QuickSlot1->SetIndex(0);
	WBP_QuickSlot2->SetIndex(1);
	WBP_QuickSlot3->SetIndex(2);
	WBP_QuickSlot4->SetIndex(3);
	WBP_QuickSlot5->SetIndex(4);
	WBP_QuickSlot6->SetIndex(5);
	WBP_QuickSlot7->SetIndex(6);
	WBP_QuickSlot8->SetIndex(7);
}

void UInventoryWidget::SetItemInfoText(FItem item)
{
	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());

	FItemString ItemString = GameInstance->GetItemString(item.Name);

	TxtItemName->SetText(FText::FromString(ItemString.Name));
	TxtItemInfo->SetText(FText::FromString(ItemString.Description));
}

void UInventoryWidget::ClearEquip(EEquipmentPart part)
{
	UEquipmentSlot* CurrentSlot = EquipSlotHead;
	switch (part)
	{
	case EEquipmentPart::E_Head:
		CurrentSlot = EquipSlotHead;
		break;
	case EEquipmentPart::E_Body:
		CurrentSlot = EquipSlotBody;
		break;
	case EEquipmentPart::E_Accessory:
		CurrentSlot = EquipSlotAcc;
		break;
	}

	CurrentSlot->SetEmpty();
}

void UInventoryWidget::SetEquipSlot(EEquipmentPart part, FItem item)
{
	UEquipmentSlot* CurrentSlot = EquipSlotHead;
	switch (part)
	{
	case EEquipmentPart::E_Head:
		CurrentSlot = EquipSlotHead;
		break;
	case EEquipmentPart::E_Body:
		CurrentSlot = EquipSlotBody;
		break;
	case EEquipmentPart::E_Accessory:
		CurrentSlot = EquipSlotAcc;
		break;
	}

	if (CurrentSlot)
	{
		CurrentSlot->SetItemInfo(item);
	}
}

void UInventoryWidget::UpdateWidgetByCategory()
{
	if (!CurrentCategoryView) return;
	CurrentCategoryView->UpdateInfo();
}

void UInventoryWidget::EmptyEntry(EItemCategory Category, int idx)
{
	UInventoryInnerWidget* EquipmentCategoryView = Cast<UInventoryInnerWidget>(WSInven->GetWidgetAtIndex((int)Category));
	if (!EquipmentCategoryView) return;

	EquipmentCategoryView->SetEmpty(idx);
}
