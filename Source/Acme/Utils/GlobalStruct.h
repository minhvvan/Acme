// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalEnum.h"
#include "GlobalStruct.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	EItemName Name;

	UPROPERTY()
	int Num;

	UPROPERTY()
	bool Equiped;

	UPROPERTY()
	EItemCategory Category;
};

UCLASS()
class ACME_API UGlobalStruct : public UObject
{
	GENERATED_BODY()
	
};
