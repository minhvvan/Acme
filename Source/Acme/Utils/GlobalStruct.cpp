// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalStruct.h"

FItem::FItem(): Name(EItemName::E_Empty), Num(0), Part(EEquipmentPart::E_None), Category(EItemCategory::E_End)
{
}

FItem::FItem(EItemCategory cate):Name(EItemName::E_Empty), Num(0), Category(cate)
{
}

void FItem::Clear()
{
	Name = EItemName::E_Empty;
	Num = 0;
	Part = EEquipmentPart::E_None;
	Category = EItemCategory::E_End;
}
