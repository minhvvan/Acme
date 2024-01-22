// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalEnum.h"
#include "AlchemicComposeWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UAlchemicComposeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVResult;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVItem;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnCompose;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnElement;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnEquipment;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnTool;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnPotion;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnFood;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnMaterial;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgElement;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgEquipment;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgTool;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgPotion;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgFood;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgMaterial;

	UPROPERTY(VisibleAnywhere)
	class AAcmeCharacter* OwnerCharacter;

protected:
	virtual void NativeConstruct();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

	UPROPERTY(VisibleAnywhere)
	EItemCategory CurrentCategory;

	UPROPERTY(VisibleAnywhere)
	class UImage* ActiveCategoryImg;

	UFUNCTION()
	void OnElementClicked();

	UFUNCTION()
	void OnEquipmentClicked();

	UFUNCTION()
	void OnToolClicked();

	UFUNCTION()
	void OnPotionClicked();

	UFUNCTION()
	void OnFoodClicked();

	UFUNCTION()
	void OnMaterialClicked();

	UFUNCTION()
	void SetItemList();	
	
	UFUNCTION()
	void SetActiveCategory();

};
