// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Item/ActiveItem.h"
#include "TotemItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API ATotemItem : public AActiveItem
{
	GENERATED_BODY()

public:
	virtual void Active() override;

	virtual void AttachBack() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATotem> TotemClass;
};
