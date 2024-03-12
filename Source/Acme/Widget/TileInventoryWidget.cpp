// Fill out your copyright notice in the Description page of Project Settings.


#include "TileInventoryWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Components/Button.h"
#include "Components/TileView.h"
#include "Acme/Data/ItemData.h"
#include "Acme/Utils/Util.h"
#include "ItemEntryWidget.h"
#include "InventoryWidget.h"

void UTileInventoryWidget::UpdateInfo()
{
	TVItem->ClearListItems();

	if (!OwnerCharacter) OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	TArray<FItem>& Items = OwnerCharacter->GetItems(Category).Get();

	for (int i = 0; i < Items.Num(); i++)
	{
		FItem& item = Items[i];

		UItemData* Data = NewObject<UItemData>();
		Data->SetItem(item);
		Data->SetIndex(i);
		Data->SetbCanShowDetail(true);
		Data->SetParentRef(this);

		TVItem->AddItem(Data);
	}
}

void UTileInventoryWidget::CloseDetailWidget()
{
	if (!ShownDetailWidget) return;

	ShownDetailWidget->RemoveFromViewport();
}

void UTileInventoryWidget::SetDetailWidget(UUserWidget* widget)
{
	ShownDetailWidget = widget;
}

void UTileInventoryWidget::SetSelectedEntry(UItemEntryWidget* entry)
{
	if (SelectedEntry)
	{
		SelectedEntry->SetUnSelected();
	}

	SelectedEntry = entry;
}

void UTileInventoryWidget::SetEmpty(int idx)
{
	UItemEntryWidget* Entry = Cast<UItemEntryWidget>(TVItem->GetItemAt(idx));
	if (!Entry) return;

	Entry->SetEmpty();
}

void UTileInventoryWidget::SetItemInfoText(FItem item)
{
	if (!Inven) return;

	Inven->SetItemInfoText(item);
}

void UTileInventoryWidget::SetInven(UInventoryWidget* parent)
{
	Inven = parent;
}
