// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementInventoryWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Components/Image.h"
#include "Components/GridPanel.h"
#include "Acme/Data/ItemData.h"
#include "Acme/Utils/Util.h"
#include "Acme/Utils/GlobalStruct.h"
#include "ItemEntryWidget.h"

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

	ElementGrid->ClearChildren();

	for (int i = 0; i < 10; i++)
	{
		FItem ItemInfo = FItem();
		ItemInfo.Name = EItemName::E_Empty;
		ItemInfo.Num = 0;
		ItemInfo.Equiped = false;
		ItemInfo.Category = EItemCategory::E_Element;

		UItemEntryWidget* Entry = Cast<UItemEntryWidget>(CreateWidget(GetWorld(), ItemEntryClass));
		Entry->SetItemInfo(ItemInfo);
		Entry->AddToViewport();

		ElementGrid->AddChildToGrid(Entry, i / 5, i % 5);
	}

	auto AllElements = OwnerCharacter->GetAllElements();
	int idx = 0;

	for (auto Element : AllElements)
	{
		UItemEntryWidget* Entry = Cast<UItemEntryWidget>(ElementGrid->GetChildAt(idx));

		int temp = (int)Element.Key;
		Entry->SetThumbnailImg(EItemName(temp));
		Entry->SetAmountTxt(Element.Value);
	}
}
