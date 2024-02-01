// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEntryWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Acme/Data/ItemData.h"
#include "Acme/Utils/Util.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TileInventoryWidget.h"
#include "Components/PanelWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Widget/ItemDDOP.h"
#include "InventoryInnerWidget.h"
#include "DetailActionWidget.h"
#include "DetailActionInnerWidget.h"
#include "Acme/AcmeGameInstance.h"

void UItemEntryWidget::SetItemInfo(FItem& info)
{
	ItemInfo = info;

	SetThumbnailImg(info.Name);
	SetAmountTxt(info.Num);
}

void UItemEntryWidget::SetIndex(int idx)
{
	Index = idx;
}

void UItemEntryWidget::SetThumbnailImg(EItemName name)
{
	UAcmeGameInstance* GameInstance = GetGameInstance<UAcmeGameInstance>();
	if (!GameInstance) return;

	UTexture2D* Image = GameInstance->GetItemImage(name);
	if (!Image) return;

	ImgItem->SetBrushFromTexture(Image);
}

void UItemEntryWidget::SetAmountTxt(int amount)
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

void UItemEntryWidget::SetEmpty()
{
	IsEmpty = true;
	ItemInfo.Category = EItemCategory::E_End;
	ItemInfo.Name = EItemName::E_Empty;
	ItemInfo.Num = 0;

	SetThumbnailImg(EItemName::E_Empty);
	SetAmountTxt(0);
}

void UItemEntryWidget::SetSelected()
{
	BorderSelected->SetBrushColor(FLinearColor(0, 50, 255, .2));
}

void UItemEntryWidget::SetUnSelected()
{
	BorderSelected->SetBrushColor(FLinearColor(0, 0, 0, 0));
}

void UItemEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UItemData* Data = Cast<UItemData>(ListItemObject);

	FItem info = Data->GetItemInfo();
	SetIndex(Data->GetIndex());
	SetItemInfo(info);

	bCanShowDetail = false;
}

FReply UItemEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

		UTileInventoryWidget* ParentWidget = Cast<UTileInventoryWidget>(GetParent()->GetOuter()->GetOuter());
		if (ParentWidget) ParentWidget->CloseDetailWidget();
	}
	else
	{
		if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && bCanShowDetail)
		{
			UTileInventoryWidget* ParentWidget = Cast<UTileInventoryWidget>(GetParent()->GetOuter()->GetOuter());
			if (ParentWidget) ParentWidget->CloseDetailWidget();

			if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

			UDetailActionWidget* Detail = Cast<UDetailActionWidget>(CreateWidget(GetWorld(), DetailWidgetClass));
			Detail->AddToViewport();
			Detail->SetPositionInViewport(InMouseEvent.GetScreenSpacePosition());

			if (ItemInfo.Name != EItemName::E_Empty)
			{
				Detail->SetInnerWidget(ItemInfo, Index);
				ParentWidget->SetDetailWidget(Detail);
			}
		}
	}
	
	return reply.NativeReply;
}

void UItemEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//ctrl = 1°³
	//shift = Àý¹Ý
	 
	if (IsEmpty) return;
	if(!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	FItem itemInfo = Player->GetItem(ItemInfo.Category, Index);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDDOP::StaticClass()));
	DragWidget->Index = Index;
	DragWidget->ItemInfo = itemInfo;
	DragWidget->WidgetRef = this;
	DragWidget->bQuickSlot = false;

	UItemEntryWidget* DragVisual = Cast<UItemEntryWidget>(CreateWidget(GetWorld(), DragWidgetClass));
	DragVisual->SetItemInfo(itemInfo);

	DragWidget->DefaultDragVisual = DragVisual;
	DragWidget->Pivot = EDragPivot::CenterCenter;

	Player->RemoveItem(ItemInfo.Category, Index);

	SetEmpty();
	OutOperation = DragWidget;
}

void UItemEntryWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

}

void UItemEntryWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	//Highliht Slot
}

void UItemEntryWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	//Highliht Slot Border
}

void UItemEntryWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	//Highliht Slot Border Off

}

bool UItemEntryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget))  return false;
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	if (DragWidget->bQuickSlot)
	{
		if (IsEmpty)
		{
			//Add
			Player->AddToInvenByIdx(DragWidget->ItemInfo, Index);
		}
		else
		{
			Player->SwapQuickAndInven(DragWidget->ItemInfo, DragWidget->Index, Index);
		}
	}
	else
	{
		if (IsEmpty)
		{
			//Add
			Player->AddToInvenByIdx(DragWidget->ItemInfo, Index);
		}
		else
		{
			//Swap
			Player->SwapInvenByIdx(DragWidget->ItemInfo, DragWidget->Index, Index);
			if (DragWidget->WidgetRef)
			{
				DragWidget->WidgetRef->SetItemInfo(ItemInfo);
			}
		}
	}

	SetItemInfo(DragWidget->ItemInfo);
	return true;
}

void UItemEntryWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget)) return;

	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	if (DragWidget->WidgetRef)
	{
		DragWidget->WidgetRef->SetItemInfo(DragWidget->ItemInfo);
	}

	OnDragCancel.Broadcast();
}