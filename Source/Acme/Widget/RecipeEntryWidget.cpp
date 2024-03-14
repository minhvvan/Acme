// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/RecipeEntryWidget.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Acme/Data/RecipeData.h"
#include "Acme/Utils/Util.h"
#include "Acme/Widget/CookPotWidget.h"
#include "Acme/Interface/CraftWidgetInterface.h"


void URecipeEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	URecipeData* Data = Cast<URecipeData>(ListItemObject);
	if (!Data) return;

	Recipe = Data->GetRecipe();
	ParentRef = Data->GetParentRef();

	UTexture2D* Image = Cast<UAcmeGameInstance>(GetGameInstance())->GetItemImage(Recipe.Result.Name);
	if (!Image) return;

	ImgItem->SetBrushFromTexture(Image);
}

FReply URecipeEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	ICraftWidgetInterface* Parent = Cast<ICraftWidgetInterface>(ParentRef);
	if (!Parent) return reply;

	Parent->SetRecipeInfo(Recipe);
	Parent->SetSelectedRecipe(this);

	SetSelectedColor(true);

	return reply;
}

void URecipeEntryWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (HoverSFX) PlaySound(HoverSFX);
}

void URecipeEntryWidget::SetSelectedColor(bool bSelected)
{
	if (bSelected)
	{
		BorderSelected->SetBrushColor(FLinearColor(0.f, 0.f, .2f, .2f));
	}
	else
	{
		BorderSelected->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, .3f));
	}
}

FRecipe URecipeEntryWidget::GetRecipe()
{
	return Recipe;
}
