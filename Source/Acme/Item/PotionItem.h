// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Item/ActiveItem.h"
#include "PotionItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API APotionItem : public AActiveItem
{
	GENERATED_BODY()
	

public:
	virtual void Active();
};
