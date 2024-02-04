// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData.h"
#include "Acme/Widget/TileInventoryWidget.h"

void UItemData::SetItem(FItem info)
{
	ItemInfo = info;
}

FItem UItemData::GetItemInfo()
{
	return ItemInfo;
}

void UItemData::SetIndex(int idx)
{
	Index = idx;
}

int UItemData::GetIndex()
{
	return Index;
}

void UItemData::SetbCanShowDetail(bool bShow)
{
	bCanShowDetail = bShow;
}

bool UItemData::GetbCanShowDetail()
{
	return bCanShowDetail;
}

void UItemData::SetParentRef(UUserWidget* parent)
{
	ParentRef = parent;
}

UUserWidget* UItemData::GetParentRef()
{
	return ParentRef;
}
