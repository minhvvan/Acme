// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalEnum.h"
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

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UProgressBar* PB_Health;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UProgressBar* PB_Satiety;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtCurrentHealth;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtMaxHealth;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtCurrentSatiety;

	void NativeOnInitialized();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void SetVisibleActionBorder(bool bVisible);

	UFUNCTION()
	void SetHealth(int CurrentHP, int MaxHP);

	UFUNCTION()
	void SetSatiety(int CurrentST);

	UFUNCTION()
	void SetStamina(int CurrentStamina);	
	
	UFUNCTION()
	void ChangeElement(EElement element, int amount);

	UFUNCTION()
	void BindStatus(class UStatComponent* StatComp);

private:
	UPROPERTY()
	float TargetHPPercent;

	UPROPERTY()
	float TargetSTPercent;

	UPROPERTY()
	float TargetStaminaPercent;

	UPROPERTY()
	float CurrentStaminaPercent;
};
