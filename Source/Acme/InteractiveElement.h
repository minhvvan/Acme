// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorInteractive.h"
#include "GlobalEnum.h"
#include "InteractiveElement.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AInteractiveElement : public AActorInteractive
{
	GENERATED_BODY()
	
public:
	AInteractiveElement();

	UFUNCTION()
	void SetElementType(EElement element);

protected:
	EElement ElementType;

public:
	virtual void Interact() override;
};
