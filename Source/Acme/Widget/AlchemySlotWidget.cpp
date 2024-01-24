// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/AlchemySlotWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/EditableTextBox.h"
#include "Acme/Widget/ItemDDOP.h"
#include "Acme/AcmeCharacter.h"

void UAlchemySlotWidget::NativeConstruct()
{

}

void UAlchemySlotWidget::SetImage()
{
	//ItemInfo·Î
	if (ItemImages[ItemInfo.Name])
	{
		ImgItem->SetBrushFromTexture(ItemImages[ItemInfo.Name]);
	}
}

void UAlchemySlotWidget::SetSlot(FItem info)
{
	SetImage();
}

FReply UAlchemySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return reply.NativeReply;
}

void UAlchemySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}

bool UAlchemySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget))  return false;

	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	ItemInfo = DragWidget->ItemInfo;
	ItemInfo.Num = 1;

	if (DragWidget->WidgetRef)
	{
		OriginRef = DragWidget->WidgetRef;

		//Player->UseItem(DragWidget->ItemInfo.Category, DragWidget->Index);
		DragWidget->WidgetRef->SetSelected();
	}

	SetSlot(ItemInfo);
	return Result;
}

void UAlchemySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);


}
