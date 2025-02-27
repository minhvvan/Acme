// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireArea.generated.h"

UCLASS()
class ACME_API AFireArea : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* Area;
	
public:	
	// Sets default values for this actor's properties
	AFireArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle LifeTimer;

	UPROPERTY(EditAnywhere)
	float LifeTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
