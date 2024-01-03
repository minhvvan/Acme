// Fill out your copyright notice in the Description page of Project Settings.


#include "TileInventoryWidget.h"
#include "AcmeCharacter.h"
#include "Components/TileView.h"
#include "ItemData.h"
#include "Util.h"

FReply UTileInventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UTileInventoryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UUtil::DebugPrint("Drag");
}

void UTileInventoryWidget::UpdateInfo()
{
	//TODO: 용량 제한 생각해봐야함
	TVItem->ClearListItems();

	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	}

	auto Items = OwnerCharacter->GetItems(Category);
	for (int i = 0; i < Items.Num(); i++)
	{
		FItem item = Items[i];

		auto Data = NewObject<UItemData>();
		FItem ItemInfo = FItem();

		ItemInfo.Name = item.Name;
		ItemInfo.Num = item.Num;
		ItemInfo.Equiped = false;
		ItemInfo.Category = item.Category;

		Data->SetItem(ItemInfo);
		TVItem->AddItem(Data);
	}
}