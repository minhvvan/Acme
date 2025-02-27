// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "RecipeEntryWidget.generated.h"



UCLASS()
class ACME_API URecipeEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* ImgItem;	
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* BorderSelected;

	UPROPERTY(EditAnywhere)
	USoundBase* HoverSFX;

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	UFUNCTION()
	void SetSelectedColor(bool bSelected);

	UFUNCTION()
	FRecipe GetRecipe();

protected:
	UPROPERTY()
	FRecipe Recipe;

	UPROPERTY()
	UUserWidget* ParentRef;

protected:
};
