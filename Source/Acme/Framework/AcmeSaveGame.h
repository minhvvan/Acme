// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AcmeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UAcmeSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UAcmeSaveGame();

public:
	UPROPERTY()
	FVector CurrentPos;

	UPROPERTY()
	int CurrentHP;

	UPROPERTY()
	int CurrentSatiety;
};
