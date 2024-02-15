// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
#include "Acme/Item/BaseItem.h"
#include "AcmeGameInstance.generated.h"

USTRUCT()
struct FComposeDetail : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemName Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItem> ResultItems;
};


USTRUCT()
struct FComposeResult : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemName Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ReactionTable;
};


USTRUCT()
struct FItemImages : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemName Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;
};


USTRUCT()
struct FItemString : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemName Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
};

USTRUCT()
struct FItemClass : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemName Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseItem> Class;
};

USTRUCT()
struct FSocketString : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESocketName Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;
};

USTRUCT()
struct FQuest : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int QusetID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItem> Request;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItem> Rewards;
};

USTRUCT()
struct FItemMesh : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;
};


UCLASS()
class ACME_API UAcmeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public: 
	UAcmeGameInstance();

protected:
	virtual void Init();

public:
	UFUNCTION()
	TArray<FItem> GetComposeResult(FItem Left, FItem Right);

	UFUNCTION()
	UTexture2D* GetItemImage(EItemName name);

	UFUNCTION()
	TSubclassOf<class ABaseItem> GetEquipItemClass(EItemName name);

	UFUNCTION()
	FItemString GetItemString(EItemName name);	
	
	UFUNCTION()
	UStaticMesh* GetItemMesh(EItemName name);

	UFUNCTION()
	FSocketString GetSocketName(ESocketName name);

	UFUNCTION()
	TArray<FQuest> GetQuest();

protected:
	UPROPERTY()
	class UDataTable* ComposeTable;

	UPROPERTY()
	class UDataTable* ItemImageTable;

	UPROPERTY()
	class UDataTable* EquipItemClassTable;

	UPROPERTY()
	class UDataTable* ItemMeshTable;

	UPROPERTY()
	class UDataTable* ItemStringTable;

	UPROPERTY()
	class UDataTable* SocketNameTable;

	UPROPERTY()
	class UDataTable* QuestTable;
};
