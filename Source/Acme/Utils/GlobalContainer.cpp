// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Utils/GlobalContainer.h"

void FItemList::SetNum(int n, EItemCategory category)
{
	ImteList.SetNum(n);

	for (int i = 0; i < n; i++)
	{
		ImteList[i] = FItem(category);
	}
}

TArray<FItem>& FItemList::Get()
{
	return ImteList;
}

int FItemList::Num()
{
	return ImteList.Num();
}
