// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/AlchemySlotWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/EditableTextBox.h"
#include "Acme/Widget/ItemDDOP.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/AcmeGameInstance.h"

void UAlchemySlotWidget::NativeConstruct()
{

}

void UAlchemySlotWidget::SetImage()
{
	UAcmeGameInstance* GameInstance = GetGameInstance<UAcmeGameInstance>();
	if (!GameInstance) return;

	UTexture2D* Image = GameInstance->GetItemImage(ItemInfo.Name);
	if (!Image) return;

	ImgItem->SetBrushFromTexture(Image);
}

void UAlchemySlotWidget::SetSlot(FItem info)
{
	SetImage();
}

void UAlchemySlotWidget::SetEmpty()
{
	ItemInfo.Category = EItemCategory::E_End;
	//ItemInfo.Equiped = false;
	ItemInfo.Name = EItemName::E_Empty;
	ItemInfo.Num = 0;

	SetImage();
	OriginRef = nullptr;
}

void UAlchemySlotWidget::UseItem()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	if (ItemInfo.Name == EItemName::E_Empty) return;

	Player->UseItem(ItemInfo.Category, Index);
	if (OriginRef)
	{
		if (ItemInfo.Num - 1 == 0) OriginRef->SetEmpty();
		else OriginRef->SetAmountTxt(ItemInfo.Num - 1);
		OriginRef->SetUnSelected();
	}

	SetEmpty();
}

bool UAlchemySlotWidget::IsEmpty()
{
	if (ItemInfo.Name == EItemName::E_Empty) return true;
	return false;
}

FItem UAlchemySlotWidget::GetItemInfo()
{
	return ItemInfo;
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

	if (DragWidget->WidgetRef)
	{
		OriginRef = DragWidget->WidgetRef;
		Index = DragWidget->Index;
		DragWidget->WidgetRef->SetSelected();
	}

	SetSlot(ItemInfo);
	return Result;
}

void UAlchemySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);


}
