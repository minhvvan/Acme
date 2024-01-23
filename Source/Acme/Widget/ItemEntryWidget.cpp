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

void UItemEntryWidget::SetItemInfo(FItem& info)
{
	Category = info.Category;

	SetThumbnailImg(info.Name);
	SetAmountTxt(info.Num);

	if (info.Equiped) SetEquipBorder();
	else SetNormalBorder();
}

void UItemEntryWidget::SetIndex(int idx)
{
	Index = idx;
}

void UItemEntryWidget::SetThumbnailImg(EItemName name)
{
	if (ItemImages[name])
	{
		ImgItem->SetBrushFromTexture(ItemImages[name]);
	}
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
	SetThumbnailImg(EItemName::E_Empty);
	SetAmountTxt(0);
	SetNormalBorder();
}

void UItemEntryWidget::SetEquipBorder()
{
	if (!EquipBorderMat) return;

	BorderItem->SetBrushFromMaterial(EquipBorderMat);
}

void UItemEntryWidget::SetNormalBorder()
{
	if (!NormalBorderMat) return;

	BorderItem->SetBrushFromMaterial(NormalBorderMat);
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

			FItem itemInfo = Player->GetItem(Category, Index);

			if (itemInfo.Name != EItemName::E_Empty)
			{
				Detail->SetInnerWidget(itemInfo, Index);
				ParentWidget->SetDetailWidget(Detail);
			}
		}
	}
	
	return reply.NativeReply;
}

void UItemEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	 
	if (IsEmpty) return;
	if(!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	FItem itemInfo = Player->GetItem(Category, Index);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDDOP::StaticClass()));
	DragWidget->Index = Index;
	DragWidget->ItemInfo = itemInfo;
	DragWidget->WidgetRef = this;

	UItemEntryWidget* DragVisual = Cast<UItemEntryWidget>(CreateWidget(GetWorld(), DragWidgetClass));
	DragVisual->SetItemInfo(itemInfo);

	DragWidget->DefaultDragVisual = DragVisual;
	DragWidget->Pivot = EDragPivot::CenterCenter;

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
	if (DragWidget->Index == Index) return false;

	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	if (DragWidget->WidgetRef)
	{
		DragWidget->WidgetRef->SetEmpty();
		Player->MoveItems(DragWidget->ItemInfo.Category, DragWidget->Index, Index);
	}

	SetItemInfo(DragWidget->ItemInfo);
	return true;
}

void UItemEntryWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget)) return;

	OnDragCancel.Broadcast();
}
