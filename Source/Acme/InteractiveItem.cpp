// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"
#include "AcmeCharacter.h"

void AInteractiveItem::Init(EItemName itemKey)
{
	//Info Setting
	Mesh->SetStaticMesh(Meshes[itemKey]);

	ItemInfo.Name = itemKey;
	ItemInfo.Num = 1;
	ItemInfo.Equiped = false;

	//TODO: Change
	ItemInfo.Category = EItemCategory::E_Armor;
}

void AInteractiveItem::Interact()
{
	if (!OverlapedCharacter) return;

	if (OverlapedCharacter->AddItem(ItemInfo))
	{
		Destroy();
	}
}