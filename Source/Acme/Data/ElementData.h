// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Acme/Utils/GlobalEnum.h"
#include "ElementData.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UElementData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	EElement Element;

	UFUNCTION()
	void SetElement(EElement e);

	UFUNCTION()
	EElement GetElement();
};
