// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"
#include "AcmeCharacter.h"
#include "Acme/Utils/Util.h"

AInteractiveItem::AInteractiveItem()
{
	ItemInfo.Name = EItemName::E_Empty;
	ItemInfo.Num = 1;
	ItemInfo.Category = EItemCategory::E_End;
}

void AInteractiveItem::Init(EItemName itemKey, EItemCategory category)
{
	//Info Setting
	if (!Meshes.Find(itemKey))
	{
		UUtil::DebugPrint("No Mesh");
		return;
	}

	Mesh->SetStaticMesh(Meshes[itemKey]);

	ItemInfo.Name = itemKey;
	ItemInfo.Num = 1;
	ItemInfo.Category = category;

	//SetName(ItemInfo.Name);
}

void AInteractiveItem::Interact()
{
	//if (!OverlapedCharacter) return;
	//if (!bCanInteract) return;

	//if (OverlapedCharacter->AddItem(ItemInfo))
	//{
	//	Destroy();
	//}
}