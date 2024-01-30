// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
#include "QuickSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgItem;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtAmount;

	UPROPERTY()
	FItem ItemInfo;

	UPROPERTY()
	int Index;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DragWidgetClass;

public:
	UFUNCTION()
	void SetItemInfo(FItem info);

	UFUNCTION()
	void SetImage(EItemName name);

	UFUNCTION()
	void SetAmount(int amount);

	UFUNCTION()
	void SetIndex(int idx);

	UFUNCTION()
	void SetEmpty();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
