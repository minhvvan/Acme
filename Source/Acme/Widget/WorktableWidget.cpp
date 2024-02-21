// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/WorktableWidget.h"
#include "Acme/Widget/RecipeEntryWidget.h"
#include "Acme/Widget/MaterialEntryWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "Acme/Data/RecipeData.h"
#include "Acme/Data/ItemData.h"

void UWorktableWidget::Init()
{
	if(!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayer()->GetPawn());
	TArray<FRecipe> Recipes = Player->GetRecipes();

	for (auto mat : Recipes)
	{
		URecipeData* Data = NewObject<URecipeData>();

		Data->SetRecipe(mat);
		Data->SetParentRef(this);

		TVRecipe->AddItem(Data);
	}
}

void UWorktableWidget::SetRecipeInfo(FRecipe recipe)
{
	CurrentRecipe = recipe;
	TVMaterial->ClearListItems();

	for (FItem item : recipe.Material)
	{
		UItemData* Data = NewObject<UItemData>();
		
		Data->SetItem(item);
		TVMaterial->AddItem(Data);
	}

	if(SelectedRecipe) SelectedRecipe->SetSelectedColor(false);

	if(!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
	ImgItem->SetBrushFromSoftTexture(GameInstance->GetItemImage(recipe.Result.Name));

	TxtDesc->SetText(FText::FromString(GameInstance->GetItemString(recipe.Result.Name).Description));
}

void UWorktableWidget::SetSelectedRecipe(URecipeEntryWidget* recipe)
{
	SelectedRecipe = recipe;
}

void UWorktableWidget::NativeConstruct()
{
	bIsFocusable = true;
	Init();

	BtnCraft->OnClicked.AddDynamic(this, &UWorktableWidget::OnClicked);
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

void UWorktableWidget::OnClicked()
{
	for (auto item : TVMaterial->GetListItems())
	{
		UMaterialEntryWidget* Material = Cast<UMaterialEntryWidget>(TVMaterial->GetEntryWidgetFromItem(item));
		if (!Material->GetbHasItem()) return;
	}

	if (!SelectedRecipe) return;
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayer()->GetPawn());

	TVMaterial->ClearListItems();
	for (FItem item : CurrentRecipe.Material)
	{
		UItemData* Data = NewObject<UItemData>();

		Player->SubmitItem(item);

		Data->SetItem(item); 
		TVMaterial->AddItem(Data);
	}

	//Add
	Player->AddItem(SelectedRecipe->GetRecipe().Result);
}