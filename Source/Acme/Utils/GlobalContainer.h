// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalStruct.h"
#include "GlobalContainer.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FItemList
{
	GENERATED_USTRUCT_BODY()

public:
	TArray<FItem> ImteList;

	void SetNum(int n, EItemCategory category);

	TArray<FItem>& Get();

	int Num();
};


UCLASS()
class ACME_API UGlobalContainer : public UObject
{
	GENERATED_BODY()
	
};
