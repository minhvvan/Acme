// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
#include "ItemEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UItemEntryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgItem;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtAmount;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtX;

public:
	UFUNCTION()
	void SetItemInfo(FItem info);

	UFUNCTION()
	void SetThumbnailImg(EItemName name);

	UFUNCTION()
	void SetAmountTxt(int amount);

protected:
	UPROPERTY(EditAnywhere)
	TMap<EItemName, UTexture2D*> ItemImages;

	UPROPERTY()
	bool IsEmpty;

	UPROPERTY()
	FItem ItemInfo;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
