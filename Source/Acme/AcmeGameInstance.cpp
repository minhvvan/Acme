// Fill out your copyright notice in the Description page of Project Settings.


#include "AcmeGameInstance.h"

UAcmeGameInstance::UAcmeGameInstance()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/Acme/Data/DT_Compose.DT_Compose'"));
		if (TABLE.Succeeded())
		{
			ComposeTable = TABLE.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/Acme/Data/DT_ItemImages.DT_ItemImages'"));
		if (TABLE.Succeeded())
		{
			ItemImageTable = TABLE.Object;
		}
	}
}

void UAcmeGameInstance::Init()
{
	Super::Init();
}

TArray<FItem> UAcmeGameInstance::GetComposeResult(FItem Left, FItem Right)
{
	TArray<FItem> Result;
	if (!ComposeTable) return Result;

	TArray<FComposeResult*> AllRows;
	ComposeTable->GetAllRows(TEXT("GetAllRows"), AllRows);

	UDataTable* Reaction;
	for (auto leftRow : AllRows)
	{
		if (leftRow->Key == Left.Name)
		{
			Reaction = leftRow->ReactionTable;
			TArray<FComposeDetail*> DetailAllRows;
			Reaction->GetAllRows(TEXT("GetAllRows"), DetailAllRows);
			for (auto row : DetailAllRows)
			{
				if (row->Key == Right.Name)
				{
					for (auto result : row->ResultItems)
					{
						Result.Add(result);
					}
				}
			}
		}
	}

	return Result;
}

UTexture2D* UAcmeGameInstance::GetItemImage(EItemName name)
{
	UTexture2D* Result = ItemImageTable->FindRow<FItemImages>(FName(TEXT("E_Empty")), TEXT(""))->Image;
	
	UEnum* ItemEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemName"), true);
	FName ItemName = FName(*ItemEnum->GetNameStringByIndex(static_cast<uint8>(name)));

	FItemImages* row = ItemImageTable->FindRow<FItemImages>(ItemName, TEXT(""));
	if (!row) return Result;

	Result = row->Image;
	
	return Result;
}