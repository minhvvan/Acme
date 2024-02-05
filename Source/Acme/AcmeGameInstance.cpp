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

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/Acme/Data/DT_ItemClass.DT_ItemClass'"));
		if (TABLE.Succeeded())
		{
			ItemClassTable = TABLE.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/Acme/Data/DT_ItemString.DT_ItemString'"));
		if (TABLE.Succeeded())
		{
			ItemStringTable = TABLE.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/Acme/Data/DT_SocketName.DT_SocketName'"));
		if (TABLE.Succeeded())
		{
			SocketNameTable = TABLE.Object;
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

TSubclassOf<class ADefaultItem> UAcmeGameInstance::GetItemClass(EItemName name)
{
	TSubclassOf<class ADefaultItem> Result = ItemClassTable->FindRow<FItemClass>(FName(TEXT("E_Empty")), TEXT(""))->Class;

	UEnum* ItemEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemName"), true);
	FName ItemName = FName(*ItemEnum->GetNameStringByIndex(static_cast<uint8>(name)));

	FItemClass* row = ItemClassTable->FindRow<FItemClass>(ItemName, TEXT(""));
	if (!row) return Result;

	Result = row->Class;

	return Result;
}

FItemString UAcmeGameInstance::GetItemString(EItemName name)
{
	FItemString Result = *ItemStringTable->FindRow<FItemString>(FName(TEXT("E_Empty")), TEXT(""));

	UEnum* ItemEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemName"), true);
	FName ItemName = FName(*ItemEnum->GetNameStringByIndex(static_cast<uint8>(name)));

	FItemString* row = ItemStringTable->FindRow<FItemString>(ItemName, TEXT(""));
	if (!row) return Result;

	Result = *row;

	return Result;
}

FSocketString UAcmeGameInstance::GetSocketName(ESocketName name)
{
	FSocketString Result = *SocketNameTable->FindRow<FSocketString>(FName(TEXT("E_End")), TEXT(""));

	UEnum* SocketEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESocketName"), true);
	FName SotcketName = FName(*SocketEnum->GetNameStringByIndex(static_cast<uint8>(name)));

	FSocketString* row = SocketNameTable->FindRow<FSocketString>(SotcketName, TEXT(""));
	if (!row) return Result;

	Result = *row;

	return Result;
}
