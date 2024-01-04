// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Acme/Utils/GlobalStruct.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FItem ItemInfo;

	UFUNCTION()
	void SetItem(FItem info);

	UFUNCTION()
	FItem GetItemInfo();
};
