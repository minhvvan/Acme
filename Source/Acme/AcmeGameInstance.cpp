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
	TArray<FItemImages*> AllRows;
	UTexture2D* Result = ItemImageTable->FindRow<FItemImages>(FName(TEXT("9"/*TODO: 아이템 이름 추가되면 계속 변경해야 함*/)), TEXT(""))->Image;

	ItemImageTable->GetAllRows(TEXT("GetAllRows"), AllRows);
	for (auto row : AllRows)
	{
		if (row->Key == name)
		{
			Result = row->Image;
		}
	}

	return Result;
}
