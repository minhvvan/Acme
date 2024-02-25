// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CraftWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCraftWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACME_API ICraftWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void SetRecipeInfo(struct FRecipe recipe) = 0;

	UFUNCTION()
	virtual void SetSelectedRecipe(class URecipeEntryWidget* recipe) = 0;
};
