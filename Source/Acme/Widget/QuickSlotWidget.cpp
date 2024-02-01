// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/QuickSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Acme/Widget/ItemDDOP.h"
#include "ItemEntryWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"
#include "Acme/DefaultItem.h"

void UQuickSlotWidget::SetItemInfo(FItem info)
{
	ItemInfo = info;
	
	SetImage(ItemInfo.Name);
	SetAmount(ItemInfo.Num);
}

void UQuickSlotWidget::SetImage(EItemName name)
{
	if(!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());

	UTexture2D* Image = GameInstance->GetItemImage(ItemInfo.Name);
	if (!Image) return;

	ImgItem->SetBrushFromTexture(Image);
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
	//TODO:�̷��� �ص� �Ǵ��� Ȯ�� �ʿ�
	ItemInfo.Category = EItemCategory::E_End;
	ItemInfo.Name = EItemName::E_Empty;

	SetImage(EItemName::E_Empty);
	SetAmount(0);
}

void UQuickSlotWidget::SetSelectBorder()
{
	if (!SelectBorderMat) return;

	BorderItem->SetBrushFromMaterial(SelectBorderMat);
}

void UQuickSlotWidget::SetUnSelectBorder()
{
	if (!NormalBorderMat) return;

	BorderItem->SetBrushFromMaterial(NormalBorderMat);
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
	DragWidget->bQuickSlot = true;

	UQuickSlotWidget* DragVisual = Cast<UQuickSlotWidget>(CreateWidget(GetWorld(), DragWidgetClass));
	DragVisual->SetItemInfo(ItemInfo);

	DragWidget->DefaultDragVisual = DragVisual;
	DragWidget->Pivot = EDragPivot::CenterCenter;

	SetEmpty();
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	FItem EmptyItem = FItem();
	Player->RemoveQuickSlot(Index);

	OutOperation = DragWidget;
}

bool UQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget)) return result;

	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	if (DragWidget->ItemInfo.Category == EItemCategory::E_Element /*�Դ� ��� �ȵ�*/)
	{
		return result;
	}

	if (DragWidget->bQuickSlot)
	{

		if (ItemInfo.Name == EItemName::E_Empty)
		{
			//Add
			Player->SetQuickSlot(DragWidget->ItemInfo, Index);
		}
		else
		{
			//swap
			Player->SwapQuickByIdx(DragWidget->ItemInfo, DragWidget->Index, Index);
		}
	}
	else
	{
		if (ItemInfo.Name == EItemName::E_Empty)
		{
			//Add
			Player->SetQuickSlot(DragWidget->ItemInfo, Index);
		}
		else
		{
			Player->SwapQuickAndInven(DragWidget->ItemInfo, DragWidget->Index, Index);
		}
	}

	SetItemInfo(DragWidget->ItemInfo);

	return result;
}

void UQuickSlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Cancel")));
}