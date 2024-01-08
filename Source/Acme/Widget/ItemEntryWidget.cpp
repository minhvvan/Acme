// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEntryWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Acme/Data/ItemData.h"
#include "Acme/Utils/Util.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Acme/Widget/ItemDDOP.h"
#include "DraggedItemWidget.h"
#include "TileInventoryWidget.h"
#include "TileInventoryWidget.h"
#include "Components/PanelWidget.h"
#include "Acme/AcmeCharacter.h"

void UItemEntryWidget::SetItemInfo(FItem info)
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
}

FReply UItemEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return reply.NativeReply;
}

void UItemEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	 
	if (IsEmpty) return;

	SetEmpty();

	UItemDDOP* DragWidget = Cast<UItemDDOP>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDDOP::StaticClass()));
	DragWidget->Index = Index;
	DragWidget->ItemInfo = ItemInfo;

	UItemEntryWidget* DragVisual = Cast<UItemEntryWidget>(CreateWidget(GetWorld(), DragWidgetClass));
	DragVisual->SetItemInfo(ItemInfo);

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
	if (!IsValid(DragWidget)) return false;

	//ÇÕÄ¡±â
	AAcmeCharacter* Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	if (!Player) return false;

	Player->MoveItems(ItemInfo.Category, DragWidget->Index, Index);

	return true;
}

void UItemEntryWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget)) return;

	OnDragCancle.Broadcast();
}
