// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Item/BaseItem.h"
#include "Acme/Utils/GlobalStruct.h"
#include "EquipmentItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AEquipmentItem : public ABaseItem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY()
	EEquipmentPart Part;

	UPROPERTY()
	FItem ItemInfo;

public:
	UFUNCTION()
	void Init(FItem newItem);

	UFUNCTION()
	void AttachToSocket(EEquipmentPart ItemPart);

	UFUNCTION()
	void AttachBack();

	UFUNCTION()
	void SetPart(EEquipmentPart newPart);

	UFUNCTION()
	UStaticMeshComponent* GetMesh();
};
