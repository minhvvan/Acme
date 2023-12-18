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

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* Border_Action;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UWidget_Element* Element_1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UWidget_Element* Element_2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UWidget_Element* Element_3;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UWidget_Element* Element_4;

	void NativeOnInitialized();

public:
	UFUNCTION()
	void SetPercent(float percent);

	UFUNCTION()
	void SetCrosshairColor(FColor color);

	UFUNCTION()
	void SetVisibleActionBorder(bool bVisible);
};
