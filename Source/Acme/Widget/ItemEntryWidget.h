// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
#include "ItemEntryWidget.generated.h"

UCLASS()
class ACME_API UItemEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgItem;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderSelected;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtAmount;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtX;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderItem;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DragWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DetailWidgetClass;

	UPROPERTY(EditAnywhere)
	USoundBase* HoverSFX;

public:
	UFUNCTION()
	void SetItemInfo(FItem& info);

	UFUNCTION()
	void SetIndex(int idx);

	UFUNCTION()
	void SetThumbnailImg(EItemName name);

	UFUNCTION()
	void SetAmountTxt(int amount);

	UFUNCTION()
	void SetEmpty();

	UFUNCTION()
	void SetSelected();

	UFUNCTION()
	void SetUnSelected();

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	UPROPERTY()
	bool IsEmpty;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY()
	FItem ItemInfo;

	UPROPERTY()
	int Index;

	UPROPERTY()
	bool bCanShowDetail;

	UPROPERTY()
	class UTileInventoryWidget* ParentTileView;

	UPROPERTY(EditAnywhere)
	UMaterial* NormalBorderMat;

	UPROPERTY(EditAnywhere)
	UMaterial* SelectBorderMat;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};