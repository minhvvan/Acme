// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Hud.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UWidget_Hud : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UWidget_Crosshair* Crosshair;

public:
	UFUNCTION()
	void SetPercent(float percent);

	UFUNCTION()
	void SetCrosshairColor(FColor color);
};
