// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Interface/CraftWidgetInterface.h"
#include "RecipeData.generated.h"

/**
 * 
 */

UCLASS()
class ACME_API URecipeData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FRecipe Recipe;

	UPROPERTY()
	UUserWidget* ParentRef;

public:
	UFUNCTION()
	void SetRecipe(FRecipe newRecipe);

	UFUNCTION()
	FRecipe GetRecipe();

	UFUNCTION()
	void SetParentRef(UUserWidget* ref);

	UFUNCTION()
	UUserWidget* GetParentRef();
};
