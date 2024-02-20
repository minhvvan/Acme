// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Data/RecipeData.h"

void URecipeData::SetRecipe(FRecipe newRecipe)
{
	Recipe = newRecipe;
}

FRecipe URecipeData::GetRecipe()
{
	return Recipe;
}
