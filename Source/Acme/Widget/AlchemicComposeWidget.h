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
	class UWidgetSwitcher* WSInven;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UListView* LVResult;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVElement;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVTool;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVMaterial;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnCompose;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnElement;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnTool;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnMaterial;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgElement;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgTool;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgMaterial;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnMinus;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnPlus;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UEditableTextBox* EdtNum;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UAlchemySlotWidget* LeftSlot;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UAlchemySlotWidget* RightSlot;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderAlert;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnOk;

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
	void OnToolClicked();

	UFUNCTION()
	void OnMaterialClicked();

	UFUNCTION()
	void OnMinusClicked();

	UFUNCTION()
	void OnPlusClicked();

	UFUNCTION()
	void OnComposeClicked();

	UFUNCTION()
	void OnTextChanged(const FText& newText);

	UFUNCTION()
	void SetNumTxt(const FText& newText);

	UFUNCTION()
	void SetItemList();		

	UFUNCTION()
	void SetActiveCategory();

	UFUNCTION()
	void ShowAlert();

	UFUNCTION()
	void OnClickedOK();

	UFUNCTION()
	UTileView* GetCurrentCategory();

public:
	UFUNCTION()
	bool AddToSlot(int idx);

	UFUNCTION()
	bool RemoveFromSlot(int idx);

protected:
	UPROPERTY(VisibleAnywhere)
	class AAcmeCharacter* OwnerCharacter;

	UPROPERTY(VisibleAnywhere)
	class UAcmeGameInstance* GameInstance;

	UPROPERTY(VisibleAnywhere)
	int LeftSlotIdx;

	UPROPERTY(VisibleAnywhere)
	int RightSlotIdx;

	UPROPERTY(VisibleAnywhere)
	int Amount;

	UPROPERTY(EditAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AInteractiveItem> DropItemClass;
};
