// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Weapon.generated.h"

UCLASS()
class ACME_API AActor_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Default, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Default, meta = (AllowPrivateAccess = "true"))
	FName HandSocket;

	UPROPERTY(EditAnywhere, Category = Default, meta = (AllowPrivateAccess = "true"))
	FName BackSocket;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Equip();

	UFUNCTION()
	void Dismantle();
};
