// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Crosshair.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UWidget_Crosshair : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* PB_Stamina;

	UPROPERTY(EditAnywhere, Category = Progress)
	UMaterialInstance* PercentMaterial;

	UPROPERTY(VisibleAnywhere, Category = Progress)
	UMaterialInstanceDynamic* MatInst;

public:
	UFUNCTION()
	void SetPercent(float percent);

	UFUNCTION()
	void SetColor(FColor color);
};
