// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultItem.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Actor_Weapon.generated.h"

UCLASS()
class ACME_API AActor_Weapon : public ADefaultItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	FName WeaponTopName;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	FName WeaponEndName;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void PlaySound();

	UFUNCTION()
	FVector GetWeponTopPos();

	UFUNCTION()
	FVector GetWeponEndPos();

	virtual void Active() override;
};
