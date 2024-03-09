// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Item/ActiveItem.h"
#include "TurretItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API ATurretItem : public AActiveItem
{
	GENERATED_BODY()
	
public:
	virtual void Active() override;

	virtual void AttachBack() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATurret> TurretClass;
};
