// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Item/EquipmentItem.h"
#include "Acme/Interface/UsableInterface.h"
#include "ActiveItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AActiveItem : public AEquipmentItem, public IUsableInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	USoundBase* ActiveSFX;
	
public:
	virtual void Active();

};
