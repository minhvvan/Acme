// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AcmePC.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AAcmePC : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void PostSeamlessTravel();

	virtual void OnPossess(APawn* aPawn) override;

	UPROPERTY()
	class UAcmeGameInstance* GameInstance;
};