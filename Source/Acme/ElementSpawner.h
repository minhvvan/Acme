// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultSpawner.h"
#include "Acme/Utils/GlobalEnum.h"
#include "ElementSpawner.generated.h"

class AInteractiveItem;

UCLASS()
class ACME_API AElementSpawner : public ADefaultSpawner
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Element, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AInteractiveItem> ElementClass;

	UPROPERTY(VisibleAnywhere, Category = Element)
	TArray<AInteractiveItem*> Elements;

public:
	// Sets default values for this actor's properties
	AElementSpawner();

	virtual void Respawn() override;

	UPROPERTY(EditAnywhere, Category = Element)
	EElement ElementType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
