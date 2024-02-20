// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/WorktableWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "Acme/Data/RecipeData.h"

void UWorktableWidget::Init()
{
	AAcmeCharacter* Player = Cast<AAcmeCharacter>(GetOwningPlayer()->GetPawn());
	TArray<FRecipe> Recipes = Player->GetRecipes();

	for (auto mat : Recipes)
	{
		URecipeData* Data = NewObject<URecipeData>();

		Data->SetRecipe(mat);
		TVRecipe->AddItem(Data);
	}
}

void UWorktableWidget::NativeConstruct()
{
	bIsFocusable = true;
	Init();
}

FReply UWorktableWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply reply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::Tab)
	{
		auto PC = Cast<APlayerController>(GetOwningPlayer()); 
		
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());

		RemoveFromParent();
	}

	return reply;
}
