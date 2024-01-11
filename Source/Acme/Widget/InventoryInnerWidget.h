// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalEnum.h"
#include "InventoryInnerWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UInventoryInnerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	EItemCategory Category;

public:
	UFUNCTION()
	virtual void UpdateInfo() {};

	UFUNCTION()
	void SetCategory(EItemCategory c);

	UFUNCTION()
	virtual void SetEuquipBorder(int idx) {};
};
