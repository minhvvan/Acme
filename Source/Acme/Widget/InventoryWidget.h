// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UHorizontalBox* HBCategory;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UButton* BtnLeft;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UButton* BtnRight;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UWidgetSwitcher* WSInven;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UTextBlock* TxtItemName;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UTextBlock* TxtItemInfo;

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
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UEquipmentSlot* EquipSlotHead;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UEquipmentSlot* EquipSlotBody;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UEquipmentSlot* EquipSlotAcc;

	UPROPERTY(EditAnywhere)
	USoundBase* OpenSFX;
	
protected:
	virtual void NativeConstruct();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

	UPROPERTY(VisibleAnyWhere, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* LeftHoverAnim;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* RightHoverAnim;

	UFUNCTION()
	void OnLeftHoverd();	
	
	UFUNCTION()
	void OnLeftLeaved();

	UFUNCTION()
	void OnLeftClicked();

	UFUNCTION()
	void OnRightHoverd();	
	
	UFUNCTION()
	void OnRightLeaved();

	UFUNCTION()
	void OnRightClicked();

	UFUNCTION()
	void ChangeCurrentView(int change);

	UFUNCTION()
	void ClearAllCategory();

	UFUNCTION()
	void SetQuickSlots();

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int Index;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UTileInventoryWidget* CurrentCategoryView;

	UPROPERTY(VisibleAnywhere)
	class UAcmeGameInstance* GameInstance;

public:
	UFUNCTION()
	void UpdateWidgetByCategory();

	UFUNCTION()
	void EmptyEntry(EItemCategory Category, int idx);

	UFUNCTION()
	void SetItemInfoText(FItem item);

	UFUNCTION()
	void ClearEquip(EEquipmentPart part);

	UFUNCTION()
	void SetEquipSlot(EEquipmentPart part, FItem item);
};
