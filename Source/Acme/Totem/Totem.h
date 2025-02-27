// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Totem.generated.h"

UCLASS()
class ACME_API ATotem : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = Default)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Default)
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, Category = Default)
	class USoundBase* HealSFX;

	UPROPERTY(EditAnywhere, Category = Default)
	class UNiagaraComponent* Niagara;

public:	
	// Sets default values for this actor's properties
	ATotem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle DestroyTimer;
	FTimerHandle HealTimer;

	UPROPERTY(EditAnywhere)
	float Time;

	UPROPERTY(EditAnywhere)
	float Interval;

	UPROPERTY(EditAnywhere)
	float Range;

	UFUNCTION()
	void Heal();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
