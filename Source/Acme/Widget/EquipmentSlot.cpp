// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/EquipmentSlot.h"
#include "Components/Image.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Widget/ItemDDOP.h"
#include "Acme/AcmeGameInstance.h"

void UEquipmentSlot::SetItemInfo(FItem item)
{
	ItemInfo = item;

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

void UEquipmentSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//Create DDOP

}

bool UEquipmentSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	//Equip
	UItemDDOP* DragWidget = Cast<UItemDDOP>(InOperation);
	if (!IsValid(DragWidget))  return false;
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	SetItemInfo(DragWidget->ItemInfo);
	Player->Equip(Part, DragWidget->ItemInfo);

	return Result;
}

void UEquipmentSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	//원상복구
}
