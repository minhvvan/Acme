// Fill out your copyright notice in the Description page of Project Settings.


#include "AcmeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Acme/Framework/AcmeSaveGame.h"
#include "Acme/Framework/MasterSaveGame.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"
#include "ImageUtils.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Serialization/BufferArchive.h"
#include "Components/SceneCaptureComponent2D.h"

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
		static ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/Acme/Data/DT_EquipItemClass.DT_EquipItemClass'"));
		if (TABLE.Succeeded())
		{
			EquipItemClassTable = TABLE.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/Acme/Data/DT_ItemMesh.DT_ItemMesh'"));
		if (TABLE.Succeeded())
		{
			ItemMeshTable = TABLE.Object;
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
	
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/Acme/Data/DT_Quest.DT_Quest'"));
		if (TABLE.Succeeded())
		{
			QuestTable = TABLE.Object;
		}
	}	
	
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/Acme/Data/DT_Item.DT_Item'"));
		if (TABLE.Succeeded())
		{
			ItemTable = TABLE.Object;
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

TSubclassOf<class ABaseItem> UAcmeGameInstance::GetEquipItemClass(EItemName name)
{
	TSubclassOf<class ABaseItem> Result = EquipItemClassTable->FindRow<FItemClass>(FName(TEXT("E_Empty")), TEXT(""))->Class;

	UEnum* ItemEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemName"), true);
	FName ItemName = FName(*ItemEnum->GetNameStringByIndex(static_cast<uint8>(name)));

	FItemClass* row = EquipItemClassTable->FindRow<FItemClass>(ItemName, TEXT(""));
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

UStaticMesh* UAcmeGameInstance::GetItemMesh(EItemName name)
{
	FItemMesh Result = *ItemMeshTable->FindRow<FItemMesh>(FName(TEXT("E_Empty")), TEXT(""));

	UEnum* ItemEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemName"), true);
	FName ItemName = FName(*ItemEnum->GetNameStringByIndex(static_cast<uint8>(name)));

	FItemMesh* row = ItemMeshTable->FindRow<FItemMesh>(ItemName, TEXT(""));
	if (!row) return Result.Mesh;

	Result = *row;
	return Result.Mesh;
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

FItem UAcmeGameInstance::GetItemInfo(EItemName name)
{
	FItem Result = *ItemTable->FindRow<FItem>(FName(TEXT("E_Empty")), TEXT(""));

	UEnum* ItemEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemName"), true);
	FName ItemName = FName(*ItemEnum->GetNameStringByIndex(static_cast<uint8>(name)));

	FItem* row = ItemTable->FindRow<FItem>(ItemName, TEXT(""));
	if (!row) return Result;

	Result = *row;

	return Result;
}

FQuest UAcmeGameInstance::GetQuest()
{
	FQuest Result;

	FName QuestID = FName("0");
	FQuest* row = QuestTable->FindRow<FQuest>(QuestID, TEXT(""));

	Result = *row;

	return Result;
}

void UAcmeGameInstance::SaveGame(AAcmeCharacter* Player)
{
	UAcmeSaveGame* NewPlayerData = NewObject<UAcmeSaveGame>();
	NewPlayerData->CurrentPos = Player->GetActorLocation();
	NewPlayerData->CurrentHP = Player->GetCurrentHP();
	NewPlayerData->CurrentSatiety = Player->GetCurrentSatiety();
	NewPlayerData->Inventory = Player->GetInventory();
	NewPlayerData->QuickSlot = Player->GetQuickSlots();

	NewPlayerData->EquipmentHead = Player->GetCurrentHead();
	NewPlayerData->EquipmentBody = Player->GetCurrentBody();
	NewPlayerData->EquipmentAcc = Player->GetCurrentAcc();

	FString slotName = FDateTime::Now().ToString();

	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, slotName, 0))
	{
		UMasterSaveGame* SaveGameList = Cast<UMasterSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveGameList"), 0));
		if (!SaveGameList)
		{
			SaveGameList = GetMutableDefault<UMasterSaveGame>();
		}

		//Update Master SaveGame
		SaveGameList->SaveGames.Add(slotName);
		if (UGameplayStatics::SaveGameToSlot(SaveGameList, TEXT("SaveGameList"), 0))
		{
			UTextureRenderTarget2D* renderTarget = NewObject<UTextureRenderTarget2D>();

			renderTarget->InitCustomFormat(1920, 1080, PF_B8G8R8A8, false);
			USceneCaptureComponent2D* SceneCapture = Player->GetThumbnailSceneCapture();
			SceneCapture->TextureTarget = renderTarget;
			SceneCapture->CaptureScene();

			ExportSaveThumbnailRT(renderTarget, slotName);
		}
	}
}

void UAcmeGameInstance::LoadGame(FString SaveSlotName)
{
	UAcmeSaveGame* SaveGame = Cast<UAcmeSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (nullptr == SaveGame)
	{
		SaveGame = GetMutableDefault<UAcmeSaveGame>();
	}

	CurrentSaveGame = SaveGame;
	GetWorld()->SeamlessTravel(TEXT("Game"));
}

UAcmeSaveGame* UAcmeGameInstance::GetCurrentSaveGame()
{
	return CurrentSaveGame;
}

FString UAcmeGameInstance::SaveGameDir(const FString& SaveGameName)
{
	return FPaths::ProjectSavedDir() + TEXT("SaveGames/") + SaveGameName + TEXT(".png");
}


UTexture2D* UAcmeGameInstance::ImportSaveThumbnail(const FString& SaveGameName)
{
	FString SaveFile = SaveGameDir(SaveGameName);

	//Suppress warning messages when we dont have a thumb yet.
	if (FPaths::FileExists(SaveFile))
	{
		return FImageUtils::ImportFileAsTexture2D(SaveFile);
	}

	return nullptr;
}

void UAcmeGameInstance::ExportSaveThumbnailRT(UTextureRenderTarget2D* TextureRenderTarget, const FString& SaveGameName)
{
	FString SaveFile = SaveGameDir(SaveGameName);
	FText PathError;
	FPaths::ValidatePath(SaveFile, &PathError);

	FTextureRenderTargetResource* resource = TextureRenderTarget->GameThread_GetRenderTargetResource();
	FReadSurfaceDataFlags readPixelFlags(RCM_UNorm);

	TArray<FColor> outBMP;
	outBMP.AddUninitialized(TextureRenderTarget->GetSurfaceWidth() * TextureRenderTarget->GetSurfaceHeight());
	resource->ReadPixels(outBMP, readPixelFlags);

	for (FColor& color : outBMP)
	{
		color.A = 255;
	}

	FIntPoint destSize(TextureRenderTarget->GetSurfaceWidth(), TextureRenderTarget->GetSurfaceHeight());
	TArray<uint8> compressedBitmap;
	FImageUtils::CompressImageArray(destSize.X, destSize.Y, outBMP, compressedBitmap);

	bool imageSavedOK = FFileHelper::SaveArrayToFile(compressedBitmap, *SaveFile);
}