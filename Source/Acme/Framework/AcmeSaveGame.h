// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Acme/Utils/GlobalStruct.h"
#include "Acme/Utils/GlobalContainer.h"
#include "Acme/Item/EquipmentItem.h"
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

	UPROPERTY()
	TMap<EItemCategory, FItemList> Inventory;

	UPROPERTY()
	TArray<FItem> QuickSlot;

	UPROPERTY()
	FItem EquipmentHead;

	UPROPERTY()
	FItem EquipmentBody;

	UPROPERTY()
	FItem EquipmentAcc;

};
