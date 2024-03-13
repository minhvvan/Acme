// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/EquipmentSlot.h"
#include "Components/Image.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Widget/ItemDDOP.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UEquipmentSlot::SetItemInfo(FItem item)
{
	ItemInfo = item;
	if (ItemInfo.Name != EItemName::E_Empty) IsEmpty = false;

	SetThumbnailImg(ItemInfo.Name);
}

void UEquipmentSlot::SetEmpty()
{
	ItemInfo.Clear();
	IsEmpty = true;

	SetThumbnailImg(ItemInfo.Name);
}

void UEquipmentSlot::SetThumbnailImg(EItemName name)
{
	if(!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	UTexture2D* Image = GameInstance->GetItemImage(name);
	if (!Image) return;

	ImgItem->SetBrushFromTexture(Image);
}

void UEquipmentSlot::NativeConstruct()
{
}

FReply UEquipmentSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}

	return reply.NativeReply;
}

void UEquipmentSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//Create DDOP
	if (IsEmpty) return;
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	UItemDDOP* DragWidget = Cast<UItemDDOP>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDDOP::StaticClass()));
	DragWidget->ItemInfo = ItemInfo;
	DragWidget->bFromQuickSlot = false;

	UEquipmentSlot* DragVisual = Cast<UEquipmentSlot>(CreateWidget(GetWorld(), DragWidgetClass));
	if (DragVisual)
	{
		DragVisual->SetItemInfo(ItemInfo);
		DragWidget->DefaultDragVisual = DragVisual;
		DragWidget->Pivot = EDragPivot::CenterCenter;
	}

	Player->UnEquip(Part);

	SetEmpty();
	OutOperation = DragWidget;
}

bool UEquipmentSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	//Equip
	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget))  return false;
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	if (DragWidget->ItemInfo.Part != Part)
	{
		//cancel
		Player->AddItem(DragWidget->ItemInfo);
		return Result;
	}

	Player->Equip(Part, DragWidget->ItemInfo);

	return Result;
}

void UEquipmentSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget))  return;
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	Player->Equip(Part, DragWidget->ItemInfo);
}
