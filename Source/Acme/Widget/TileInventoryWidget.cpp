// Fill out your copyright notice in the Description page of Project Settings.


#include "TileInventoryWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Components/GridPanel.h"
#include "Acme/Data/ItemData.h"
#include "Acme/Utils/Util.h"
#include "ItemEntryWidget.h"

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
	ItemGrid->ClearChildren();

	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	}

	TArray<FItem> Items = OwnerCharacter->GetItems(Category).Get();
	for (int i = 0; i < Items.Num(); i++)
	{
		FItem item = Items[i];

		UItemEntryWidget* Entry = Cast<UItemEntryWidget>(CreateWidget(GetWorld(), ItemEntryClass));
		Entry->SetItemInfo(item);
		Entry->AddToViewport();

		ItemGrid->AddChildToGrid(Entry, i/5, i%5);
	}
}