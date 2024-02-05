// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultItem.h"
#include "EquipmentItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AEquipmentItem : public ADefaultItem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY()
	EEquipmentPart Part;

public:
	UFUNCTION()
	void AttachToSocket(EEquipmentPart ItemPart);

	UFUNCTION()
	void SetPart(EEquipmentPart newPart);
};
