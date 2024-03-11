// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveGameData.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API USaveGameData : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString SlotName;


};
