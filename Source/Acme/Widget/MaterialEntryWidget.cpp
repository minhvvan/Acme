// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/MaterialEntryWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Acme/Data/ItemData.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/AcmeCharacter.h"

void UMaterialEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UItemData* Data = Cast<UItemData>(ListItemObject);

	UAcmeGameInstance* GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
	ImgItem->SetBrushFromTexture(GameInstance->GetItemImage(Data->ItemInfo.Name));
	TxtNum->SetText(FText::AsNumber(Data->ItemInfo.Num));

	AAcmeCharacter* Player = Cast<AAcmeCharacter>(GetOwningPlayer()->GetPawn());
	if (!Player) return;

	int OwnItemNums = Player->GetItemNums(Data->ItemInfo);
	bHasItem = OwnItemNums >= Data->ItemInfo.Num;

	TxtOwnNum->SetText(FText::AsNumber(OwnItemNums));

	UpdateBorderState();
}

bool UMaterialEntryWidget::GetbHasItem()
{
	return bHasItem;
}

void UMaterialEntryWidget::UpdateBorderState()
{
	if (bHasItem)
	{
		BorderHeader->SetBrushColor(FLinearColor(.4f, 0.4f, 0.4f));
	}
	else
	{
		BorderHeader->SetBrushColor(FLinearColor(1.f, 0.f, 0.f));
	}
}
