// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/CookPotWidget.h"
#include "Acme/Widget/RecipeEntryWidget.h"
#include "Acme/Widget/MaterialEntryWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "Components/EditableTextBox.h"
#include "Acme/Data/RecipeData.h"
#include "Acme/Data/ItemData.h"

void UCookPotWidget::Init()
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

	Amount = 0;
}

void UCookPotWidget::SetRecipeInfo(FRecipe recipe)
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
	TxtName->SetText(FText::FromString(GameInstance->GetItemString(recipe.Result.Name).Name));
}

void UCookPotWidget::SetSelectedRecipe(URecipeEntryWidget* recipe)
{
	SelectedRecipe = recipe;
}

void UCookPotWidget::NativeConstruct()
{
	bIsFocusable = true;
	Init();

	BtnCraft->OnClicked.AddDynamic(this, &UCookPotWidget::OnClickedCraft);
	BtnMinus->OnClicked.AddDynamic(this, &UCookPotWidget::OnClickedMinus);
	BtnPlus->OnClicked.AddDynamic(this, &UCookPotWidget::OnClickedPlus);
}

FReply UCookPotWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
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

void UCookPotWidget::OnClickedCraft()
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

		for (int i = 0; i < Amount; i++)
		{
			Player->SubmitItem(item);
		}

		Data->SetItem(item); 
		TVMaterial->AddItem(Data);
	}

	//Add
	for (int i = 0; i < Amount; i++)
	{
		Player->AddItem(SelectedRecipe->GetRecipe().Result);
	}

	//Reset
	Amount = 0;
	EdtNum->SetText(FText::AsNumber(Amount));
}

void UCookPotWidget::OnClickedMinus()
{
	if (!SelectedRecipe) return;

	Amount--;
	if (Amount < 0) Amount = 0;

	EdtNum->SetText(FText::AsNumber(Amount));
}

void UCookPotWidget::OnClickedPlus()
{
	if (!SelectedRecipe) return;
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayer()->GetPawn());

	int minNum = 99;
	for (FItem item : CurrentRecipe.Material)
	{
		minNum = FMath::Min(minNum, Player->GetItemNums(item));
	}

	if (Amount >= minNum)
	{
		Amount = minNum;
		EdtNum->SetText(FText::AsNumber(Amount));
		return;
	}

	Amount++;

	if (Amount > 99) Amount = 99;
	EdtNum->SetText(FText::AsNumber(Amount));
}

