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
	class UTileView* TVItem;

protected:
	UPROPERTY(VisibleAnywhere)
	class AAcmeCharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ItemEntryClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UUserWidget> ShownDetailWidget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UItemEntryWidget> SelectedEntry;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInventoryWidget> Inven;

public:
	virtual void UpdateInfo() override;

	UFUNCTION()
	void CloseDetailWidget();

	UFUNCTION()
	void SetDetailWidget(UUserWidget* widget);

	UFUNCTION()
	void SetSelectedEntry(UItemEntryWidget* entry);
	
	virtual void SetEmpty(int idx);

	UFUNCTION()
	void SetItemInfoText(FItem item);

	UFUNCTION()
	void SetInven(UInventoryWidget* parent);
};
