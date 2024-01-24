// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalStruct.h"
#include "Acme/Utils/GlobalEnum.h"
#include "AlchemySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UAlchemySlotWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderItem;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgItem;

protected:
	UPROPERTY(EditAnywhere)
	TMap<EItemName, UTexture2D*> ItemImages;

	UPROPERTY(VisibleAnywhere)
	FItem ItemInfo;

	UPROPERTY(VisibleAnywhere)
	class AAcmeCharacter* Player;

	UPROPERTY(VisibleAnywhere)
	class UItemEntryWidget* OriginRef;

public:
	UFUNCTION()
	void SetImage();

	UFUNCTION()
	void SetSlot(FItem info);


protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);


};
