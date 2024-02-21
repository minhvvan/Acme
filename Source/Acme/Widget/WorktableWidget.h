// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/AcmeGameInstance.h"
#include "WorktableWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UWorktableWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(meta = (BindWidget))
	class UTileView* TVRecipe;	
	
	UPROPERTY(meta = (BindWidget))
	class UTileView* TVMaterial;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnCraft;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgItem;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtDesc;

public:
	UFUNCTION()
	void Init();

	UFUNCTION()
	void SetRecipeInfo(struct FRecipe recipe);

	UFUNCTION()
	void SetSelectedRecipe(class URecipeEntryWidget* recipe);

protected:
	virtual void NativeConstruct();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

	UFUNCTION()
	void OnClicked();

protected:
	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY()
	FRecipe CurrentRecipe;

	UPROPERTY()
	URecipeEntryWidget* SelectedRecipe;
};
