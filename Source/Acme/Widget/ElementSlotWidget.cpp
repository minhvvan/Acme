// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/ElementSlotWidget.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Acme/Widget/ItemDDOP.h"

void UElementSlotWidget::SetImage(EElement element)
{
	if (ElementImages[element])
	{
		ImageElement->SetBrushFromTexture(ElementImages[element]);
	}
}

void UElementSlotWidget::NativeOnInitialized()
{

}

FReply UElementSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	}

	return reply.NativeReply;
}

void UElementSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UElementSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{


	return false;
}

void UElementSlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
}
