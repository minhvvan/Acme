// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuideWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UGuideWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnOk;	
	
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CBOpenNext;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnLeft;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnRight;	
	
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* SwitchGuide;
	

	virtual void NativeConstruct();

private:
	UFUNCTION()
	void OnOKClicked();

	UFUNCTION()
	void OnLeftClicked();

	UFUNCTION()
	void OnRightClicked();

	UPROPERTY()
	int CurrentIdx;
	
};
