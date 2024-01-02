// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryInnerWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UInventoryInnerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void UpdateInfo() {};
};
