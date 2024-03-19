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

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderItem;

protected:
	UPROPERTY()
	FItem ItemInfo;

	UPROPERTY()
	int Index;

	UPROPERTY()
	bool bClickable = true;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DragWidgetClass;

	UPROPERTY(EditAnywhere)
	UMaterial* NormalBorderMat;

	UPROPERTY(EditAnywhere)
	UMaterial* SelectBorderMat;

	UPROPERTY(VisibleAnywhere)
	class AAcmeCharacter* Player;

	UPROPERTY(VisibleAnywhere)
	class UAcmeGameInstance* GameInstance;

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

	UFUNCTION()
	void SetSelectBorder();

	UFUNCTION()
	void SetUnSelectBorder();

	UFUNCTION()
	void SetClickable(bool bClick);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
