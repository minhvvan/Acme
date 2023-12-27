// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetIndicator.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UWidgetIndicator : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtName;

public:
	UFUNCTION()
	void SetName(FString name);
};
