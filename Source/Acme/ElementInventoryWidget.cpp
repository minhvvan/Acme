// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementInventoryWidget.h"
#include "AcmeCharacter.h"
#include "Components/Image.h"
#include "Components/TileView.h"
#include "ItemData.h"
#include "Util.h"

void UElementInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UElementInventoryWidget::UpdateInfo()
{
	//TODO: DO Something
	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	}

	auto CurrentElements = OwnerCharacter->GetElements();

	ImgElement1->SetBrushFromTexture(ElementImages[CurrentElements[0]]);
	ImgElement2->SetBrushFromTexture(ElementImages[CurrentElements[1]]);
	ImgElement3->SetBrushFromTexture(ElementImages[CurrentElements[2]]);
	ImgElement4->SetBrushFromTexture(ElementImages[CurrentElements[3]]);

	TVElement->ClearListItems();

	auto AllElements = OwnerCharacter->GetAllElements();
	for (auto Element : AllElements)
	{
		auto Data = NewObject<UItemData>();
		FItem ItemInfo = FItem();
		switch (Element.Key)
		{
		case EElement::E_Fire:
			ItemInfo.Name = EItemName::E_Fire;
			break;		
		case EElement::E_Water:
			ItemInfo.Name = EItemName::E_Water;
			break;
		case EElement::E_Earth:
			ItemInfo.Name = EItemName::E_Earth;
			break;
		case EElement::E_Air:
			ItemInfo.Name = EItemName::E_Air;
			break;
		case EElement::E_Ice:
			ItemInfo.Name = EItemName::E_Ice;
			break;
		case EElement::E_Thunder:
			ItemInfo.Name = EItemName::E_Thunder;
			break;
		}

		ItemInfo.Num = Element.Value;
		ItemInfo.Equiped = false;
		ItemInfo.Category = EItemCategory::E_Element;

		Data->SetItem(ItemInfo);

		TVElement->AddItem(Data);
	}
}
