// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/QuickSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Acme/Widget/ItemDDOP.h"
#include "ItemEntryWidget.h"
#include "Acme/AcmeCharacter.h"

void UQuickSlotWidget::SetItemInfo(FItem info)
{
	ItemInfo = info;
	
	SetImage(ItemInfo.Name);
	SetAmount(ItemInfo.Num);
}

void UQuickSlotWidget::SetImage(EItemName name)
{
	if (ItemImages[name])
	{
		ImgItem->SetBrushFromTexture(ItemImages[name]);
	}
}

void UQuickSlotWidget::SetAmount(int amount)
{
	TxtAmount->SetText(FText::AsNumber(amount));

	if (amount == 0)
	{
		TxtAmount->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TxtAmount->SetVisibility(ESlateVisibility::Visible);
	}
}

void UQuickSlotWidget::SetIndex(int idx)
{
	Index = idx;
}

void UQuickSlotWidget::SetEmpty()
{
	SetImage(EItemName::E_Empty);
	SetAmount(0);
}

FReply UQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}

	return reply.NativeReply;
}

void UQuickSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDDOP::StaticClass()));
	DragWidget->Index = Index;
	DragWidget->ItemInfo = ItemInfo;

	UQuickSlotWidget* DragVisual = Cast<UQuickSlotWidget>(CreateWidget(GetWorld(), DragWidgetClass));
	DragVisual->SetItemInfo(ItemInfo);

	DragWidget->DefaultDragVisual = DragVisual;
	DragWidget->Pivot = EDragPivot::CenterCenter;

	SetEmpty();
	AAcmeCharacter* Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	if (!Player) return;

	FItem EmptyItem = FItem();
	Player->SetQuickSlot(EmptyItem, Index);

	OutOperation = DragWidget;
}

bool UQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget)) return false;

	AAcmeCharacter* Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	if (!Player) return false;

	if (DragWidget->ItemInfo.Category == EItemCategory::E_Element || DragWidget->ItemInfo.Category == EItemCategory::E_Equipment)
	{
		return false;
	}

	SetItemInfo(DragWidget->ItemInfo);
	Player->SetQuickSlot(ItemInfo, Index);

	return result;
}

void UQuickSlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Cancel")));
}
