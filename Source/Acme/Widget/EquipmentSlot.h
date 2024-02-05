// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
#include "EquipmentSlot.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UEquipmentSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgItem;


protected:
	UPROPERTY(VisibleAnywhere)
	class AAcmeCharacter* Player;

	UPROPERTY(EditAnywhere)
	EEquipmentPart Part;

	UPROPERTY(VisibleAnywhere)
	FItem ItemInfo;

	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

public:


protected:
	UFUNCTION()
	void SetItemInfo(FItem item);

	UFUNCTION()
	void SetThumbnailImg(EItemName name);

	virtual void NativeConstruct();

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
