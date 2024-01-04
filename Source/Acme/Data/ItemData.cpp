// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData.h"

void UItemData::SetItem(FItem info)
{
	ItemInfo = info;
}

FItem UItemData::GetItemInfo()
{
	return ItemInfo;
}
