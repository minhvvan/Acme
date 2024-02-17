// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/RewardEntryWidget.h"
#include "Acme/Data/ItemData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Acme/AcmeGameInstance.h"


void URewardEntryWidget::NativeOnInitialized()
{
	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
}

void URewardEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UItemData* Data = Cast<UItemData>(ListItemObject);

	FItem ItemInfo = Data->ItemInfo;
	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());

	{
		UTexture2D* Src = GameInstance->GetItemImage(ItemInfo.Name);
		if (Src) ImgItem->SetBrushFromTexture(Src);
	}

	{
		FItemString Src = GameInstance->GetItemString(ItemInfo.Name);
		TxtName->SetText(FText::FromString(Src.Name));
	}

	{
		TxtNum->SetText(FText::AsNumber(ItemInfo.Num));
	}
}
