// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEntryWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemData.h"

void UItemEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UItemData* Data = Cast<UItemData>(ListItemObject);
	FItem ItemInfo = Data->GetItemInfo();

	//TODO: null check
	ImgItem->SetBrushFromTexture(ItemImages[ItemInfo.Name]);
	TxtAmount->SetText(FText::AsNumber(ItemInfo.Num));

	if (ItemInfo.Num == 0)
	{
		ImgItem->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, .5f));
	}
}
