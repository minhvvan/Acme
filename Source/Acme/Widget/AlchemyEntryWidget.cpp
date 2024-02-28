// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/AlchemyEntryWidget.h"
#include "Acme/Widget/AlchemicComposeWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Acme/Data/ItemData.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"

void UAlchemyEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAlchemyEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UItemData* Data = Cast<UItemData>(ListItemObject);

	FItem info = Data->GetItemInfo();
	SetIndex(Data->GetIndex());
	SetItemInfo(info);

	SetUnSelected();

	ParentWidget = Cast<UAlchemicComposeWidget>(Data->GetParentRef());
	if (!ParentWidget) return;
}

void UAlchemyEntryWidget::SetItemInfo(FItem& info)
{
	ItemInfo = info;

	SetThumbnailImg(info.Name);
	SetAmountTxt(info.Num);
}

void UAlchemyEntryWidget::SetIndex(int idx)
{
	Index = idx;
}

void UAlchemyEntryWidget::SetSelected()
{
	BorderSelected->SetBrushColor(FLinearColor(0.f, .2f, 1.f));
}

void UAlchemyEntryWidget::SetUnSelected()
{
	BorderSelected->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.f));
}

FReply UAlchemyEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (IsEmpty) return Result;

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		//Add to Slot
		if (ParentWidget && ParentWidget->AddToSlot(Index))
		{
			SetSelected();
		}
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		//Remove from Slot
		if (ParentWidget && ParentWidget->RemoveFromSlot(Index))
		{
			SetUnSelected();
		}
	}

	return Result;
}

void UAlchemyEntryWidget::SetThumbnailImg(EItemName name)
{
	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	UTexture2D* Image = GameInstance->GetItemImage(name);
	if (!Image) return;

	ImgItem->SetBrushFromTexture(Image);
}

void UAlchemyEntryWidget::SetAmountTxt(int amount)
{
	if (amount == 0)
	{
		ImgItem->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, .5f));
		TxtAmount->SetVisibility(ESlateVisibility::Hidden);
		TxtX->SetVisibility(ESlateVisibility::Hidden);
		IsEmpty = true;
	}
	else
	{
		TxtAmount->SetText(FText::AsNumber(amount));
		TxtAmount->SetVisibility(ESlateVisibility::Visible);
		TxtX->SetVisibility(ESlateVisibility::Visible);
		ImgItem->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		IsEmpty = false;
	}
}
