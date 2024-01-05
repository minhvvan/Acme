// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEntryWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Acme/Data/ItemData.h"
#include "Acme/Utils/Util.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Acme/Widget/ItemDDOP.h"
#include "Acme/Widget/DraggedItemWidget.h"

void UItemEntryWidget::SetItemInfo(FItem info)
{
	SetThumbnailImg(info.Name);
	SetAmountTxt(info.Num);
}

void UItemEntryWidget::SetThumbnailImg(EItemName name)
{
	ImgItem->SetBrushFromTexture(ItemImages[name]);
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

FReply UItemEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UItemEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (IsEmpty) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Drag: %s"), *GetName()));

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	 
	UItemDDOP* DragWidget = Cast<UItemDDOP>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDDOP::StaticClass()));

	DragWidget->WidgetRef = this;
	DragWidget->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	//TODO: Same ref-> strange 
	DragWidget->DefaultDragVisual = this;
	SetVisibility(ESlateVisibility::HitTestInvisible);

	DragWidget->Pivot = EDragPivot::MouseDown;
	DragWidget->Payload = this;

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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Drop: %s"), *GetName()));

	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);

	if (!IsValid(DragWidget)) return false;

	const FVector2D DragWindowOffset = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	const FVector2D DragWindowOffsetResult = DragWindowOffset - DragWidget->DragOffset;

	DragWidget->WidgetRef->AddToViewport();
	DragWidget->WidgetRef->SetVisibility(ESlateVisibility::Visible);
	DragWidget->WidgetRef->SetPositionInViewport(DragWindowOffsetResult, false);

	return true;
}