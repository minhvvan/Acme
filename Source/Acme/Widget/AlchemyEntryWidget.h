// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Acme/Utils/GlobalStruct.h"
#include "AlchemyEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UAlchemyEntryWidget : public UUserWidget, public IUserObjectListEntry
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

protected:
	UPROPERTY()
	FItem ItemInfo;

	UPROPERTY()
	int Index;

	UPROPERTY()
	bool IsEmpty;	
	
	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

	UPROPERTY()
	class UAlchemicComposeWidget* ParentWidget;

public:
	virtual void NativeConstruct();

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	void SetItemInfo(FItem& info);

	UFUNCTION()
	void SetIndex(int idx);

	UFUNCTION()
	void SetSelected();

	UFUNCTION()
	void SetUnSelected();

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	UFUNCTION()
	void SetThumbnailImg(EItemName name);

	UFUNCTION()
	void SetAmountTxt(int amount);
};
