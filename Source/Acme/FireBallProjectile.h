// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBallProjectile.generated.h"

UCLASS()
class ACME_API AFireBallProjectile : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;	
	
	UPROPERTY(EditAnywhere)
	class USphereComponent* CollisionComponent;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFireArea> FireAreaClass;

public:	
	// Sets default values for this actor's properties
	AFireBallProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	bool bHit;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
	void SpawnFireArea(const FHitResult& ImpactResult);
};
