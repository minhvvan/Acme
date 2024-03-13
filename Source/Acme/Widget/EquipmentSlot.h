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

	UPROPERTY()
	bool IsEmpty = true;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DragWidgetClass;

public:
	UFUNCTION()
	void SetEmpty();

	UFUNCTION()
	void SetItemInfo(FItem item);
protected:
	UFUNCTION()
	void SetThumbnailImg(EItemName name);

	virtual void NativeConstruct();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
