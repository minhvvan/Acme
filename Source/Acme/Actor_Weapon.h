// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlobalEnum.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, Category = Default, meta = (AllowPrivateAccess = "true"))
	FName HandSocket;

	UPROPERTY(EditAnywhere, Category = Default, meta = (AllowPrivateAccess = "true"))
	FName BackSocket;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SFX, meta = (AllowPrivateAccess = "true"))
	TMap<EElement, class USoundBase*> SFXList;

	UPROPERTY()
	EElement CurrentType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Equip();

	UFUNCTION()
	void Dismantle();

	UFUNCTION()
	void PlaySound();
};
