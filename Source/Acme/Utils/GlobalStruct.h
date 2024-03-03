// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalEnum.h"
#include "GlobalStruct.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FItemStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;
};


USTRUCT(Atomic, BlueprintType)
struct FItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FItem();

	FItem(EItemCategory cate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Num;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentPart Part;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAddQuick;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemStat ItemStat;

	void Clear();
};

UCLASS()
class ACME_API UGlobalStruct : public UObject
{
	GENERATED_BODY()
	
};
