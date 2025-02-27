// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Turret.generated.h"

UCLASS()
class ACME_API ATurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurret();

protected:
	UPROPERTY(EditAnywhere, Category = Default)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Default)
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, Category = Default)
	class UNiagaraComponent* Niagara;

	UPROPERTY(EditAnywhere, Category = Default)
	class USoundBase* FireSFX;	
	
	UPROPERTY(EditAnywhere, Category = Default)
	class USoundBase* FindEmermySFX;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void PlayFireSFX();	
	
	UFUNCTION()
	void PlayFindEnermySFX();

	UFUNCTION()
	void PlayFireFX(bool bOnTarget);

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void SetTarget(class ACharacterMonster* newTarget);

protected:
	UPROPERTY(VisibleAnywhere)
	ACharacterMonster* Target;

	UPROPERTY(EditAnywhere)
	int Damage;

	UPROPERTY(EditAnywhere)
	float Time;

	//UPROPERTY()
	FTimerHandle DestroyTimer;
};
