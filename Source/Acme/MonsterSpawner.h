// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

class APawn_Monster;

UCLASS()
class ACME_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = Monster)
	class UBoxComponent* Area;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawn_Monster> MonsterClass;

	UPROPERTY(VisibleAnywhere, Category = Monster)
	TArray<APawn_Monster*> Monsters;

public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

	UFUNCTION()
	void Respawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = Setting, meta = (AllowPrivateAccess = "true"))
	int MaxPopulation;

	UPROPERTY(EditAnywhere, Category = Setting, meta = (AllowPrivateAccess = "true"))
	float RespawnInterval;

private:
	FTimerHandle RespawnHandle;
};
