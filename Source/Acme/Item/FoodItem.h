// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Item/ActiveItem.h"
#include "FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AFoodItem : public AActiveItem
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();

	virtual void Active();

private:
	UPROPERTY()
	int Satiety;
};
