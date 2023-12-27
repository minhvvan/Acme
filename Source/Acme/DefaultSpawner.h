// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultSpawner.generated.h"

UCLASS()
class ACME_API ADefaultSpawner : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = Monster)
	class UBoxComponent* Area;

public:	
	// Sets default values for this actor's properties
	ADefaultSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Respawn() {};

	UPROPERTY(EditAnywhere, Category = Setting, meta = (AllowPrivateAccess = "true"))
	int MaxPopulation;

	UPROPERTY(EditAnywhere, Category = Setting, meta = (AllowPrivateAccess = "true"))
	float RespawnInterval;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	FTimerHandle RespawnHandle;
};
