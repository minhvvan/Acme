// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
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

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UQuickSlotWidget* WBP_QuickSlot1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UQuickSlotWidget* WBP_QuickSlot2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UQuickSlotWidget* WBP_QuickSlot3;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UQuickSlotWidget* WBP_QuickSlot4;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UQuickSlotWidget* WBP_QuickSlot5;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UQuickSlotWidget* WBP_QuickSlot6;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UQuickSlotWidget* WBP_QuickSlot7;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UQuickSlotWidget* WBP_QuickSlot8;

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
	void SetHealth(int CurrentHP, int MaxHP);

	UFUNCTION()
	void SetSatiety(int CurrentST);

	UFUNCTION()
	void SetStamina(int CurrentStamina);	
	
	UFUNCTION()
	void SetQuickSlots(TArray<FItem> QuickSlots);

	UFUNCTION()
	void BindStatus(class UStatComponent* StatComp);

	UFUNCTION()
	void ChangeSelectedSlot(int idx);

private:
	UPROPERTY()
	float TargetHPPercent;

	UPROPERTY()
	float TargetSTPercent;

	UPROPERTY()
	float TargetStaminaPercent;

	UPROPERTY()
	float CurrentStaminaPercent;

	UPROPERTY()
	int CurrentQuickSlotIdx;

	UPROPERTY()
	TArray<UQuickSlotWidget*> QuickSlotWidgets;
};
