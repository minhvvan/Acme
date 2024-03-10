// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MasterSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UMasterSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMasterSaveGame();

public:
	UPROPERTY()
	TArray<FString> SaveGames;
};
