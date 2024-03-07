// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/AlchemySlotWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/EditableTextBox.h"
#include "Acme/Widget/ItemDDOP.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"

void UAlchemySlotWidget::NativeConstruct()
{

}

void UAlchemySlotWidget::SetImage()
{
	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	UTexture2D* Image = GameInstance->GetItemImage(ItemInfo.Name);
	if (!Image) return;

	ImgItem->SetBrushFromTexture(Image);
}

void UAlchemySlotWidget::SetSlot(FItem info, int idx)
{
	ItemInfo = info;
	ItemIndex = idx;
	SetImage();
}

void UAlchemySlotWidget::SetEmpty()
{
	ItemInfo.Clear();
	ItemIndex = -1;
	SetImage();
}

bool UAlchemySlotWidget::IsSame(FItem item, int idx)
{
	return ItemInfo.Name == item.Name && ItemIndex == idx;
}

void UAlchemySlotWidget::Compose()
{
	SetEmpty();
}

bool UAlchemySlotWidget::IsEmpty()
{
	if (ItemInfo.Name == EItemName::E_Empty) return true;
	return false;
}

FItem UAlchemySlotWidget::GetItemInfo()
{
	return ItemInfo;
}
