// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultSpawner.h"
#include "Acme/Utils/GlobalEnum.h"
#include "InteractiveEnvSpawner.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AInteractiveEnvSpawner : public ADefaultSpawner
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AInteractiveItem> EnvClass;

	UPROPERTY(VisibleAnywhere, Category = Default)
	TArray<AInteractiveItem*> Enves;

	UPROPERTY(EditAnywhere, Category = Default)
	EItemName ItemName;

public:
	// Sets default values for this actor's properties
	AInteractiveEnvSpawner();

	virtual void Respawn() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

};
