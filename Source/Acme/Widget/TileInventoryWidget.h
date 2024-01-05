// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryInnerWidget.h"
#include "Acme/Utils/GlobalEnum.h"
#include "TileInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UTileInventoryWidget : public UInventoryInnerWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UGridPanel* ItemGrid;

	UPROPERTY(VisibleAnywhere)
	class AAcmeCharacter* OwnerCharacter;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ItemEntryClass;

public:
	virtual void UpdateInfo() override;
};
