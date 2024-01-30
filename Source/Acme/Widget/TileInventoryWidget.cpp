// Fill out your copyright notice in the Description page of Project Settings.


#include "TileInventoryWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Components/GridPanel.h"
#include "Components/Button.h"
#include "Acme/Data/ItemData.h"
#include "Acme/Utils/Util.h"
#include "ItemEntryWidget.h"

void UTileInventoryWidget::UpdateInfo()
{
	ItemGrid->ClearChildren();

	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	}

	TArray<FItem>& Items = OwnerCharacter->GetItems(Category).Get();
	for (int i = 0; i < Items.Num(); i++)
	{
		FItem& item = Items[i];

		UItemEntryWidget* Entry = Cast<UItemEntryWidget>(CreateWidget(GetWorld(), ItemEntryClass));
		Entry->SetItemInfo(item);
		Entry->SetIndex(i);
		Entry->AddToViewport();

		Entry->OnDragCancel.AddUObject(this, &UTileInventoryWidget::UpdateInfo);

		ItemGrid->AddChildToGrid(Entry, i/5, i%5);
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

void UTileInventoryWidget::SetEmpty(int idx)
{
	UItemEntryWidget* Entry = Cast<UItemEntryWidget>(ItemGrid->GetChildAt(idx));
	if (!Entry) return;

	Entry->SetEmpty();
}
