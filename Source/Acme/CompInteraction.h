// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "CompInteraction.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UCompInteraction : public USphereComponent
{
	GENERATED_BODY()

public:
	UCompInteraction();
	
protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
