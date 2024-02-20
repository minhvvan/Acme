// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Acme/AcmeGameInstance.h"
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

public:
	UFUNCTION()
	void SetRecipe(FRecipe newRecipe);

	UFUNCTION()
	FRecipe GetRecipe();
};
