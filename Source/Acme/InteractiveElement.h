// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorInteractive.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
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

	virtual void BeginPlay() override;

protected:
	EElement ElementType;

	FItem ItemInfo;

public:
	virtual void Interact() override;
};
