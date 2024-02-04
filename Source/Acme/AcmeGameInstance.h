// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
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
	TSubclassOf<class ADefaultItem> Class;
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
	TSubclassOf<class ADefaultItem> GetItemClass(EItemName name);

protected:
	UPROPERTY()
	class UDataTable* ComposeTable;

	UPROPERTY()
	class UDataTable* ItemImageTable;

	UPROPERTY()
	class UDataTable* ItemClassTable;
};
