// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Acme/Utils/GlobalStruct.h"
#include "ItemDDOP.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UItemDDOP : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FItem ItemInfo;
};
