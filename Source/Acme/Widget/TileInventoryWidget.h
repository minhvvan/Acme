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

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ItemEntryClass;

	TObjectPtr<UUserWidget> ShownDetailWidget;

public:
	virtual void UpdateInfo() override;

	UFUNCTION()
	void CloseDetailWidget();

	UFUNCTION()
	void SetDetailWidget(UUserWidget* widget);

	virtual void SetEuquipBorder(int idx) override;

	virtual void SetNormalBorder(int idx) override;
};
