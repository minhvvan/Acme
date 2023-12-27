// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultSpawner.h"
#include "MonsterSpawner.generated.h"

class ACharacterMonster;

UCLASS()
class ACME_API AMonsterSpawner : public ADefaultSpawner
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACharacterMonster> MonsterClass;

	UPROPERTY(VisibleAnywhere, Category = Monster)
	TArray<ACharacterMonster*> Monsters;

public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

	virtual void Respawn() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
