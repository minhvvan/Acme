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

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int Idx;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInventoryInnerWidget* CurrentCategoryView;

public:
	UFUNCTION()
	void UpdateWidgetByCategory();
};
