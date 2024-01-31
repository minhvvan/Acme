// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor_Weapon.h"
#include "SwordActor.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API ASwordActor : public AActor_Weapon
{
	GENERATED_BODY()

public:
	ASwordActor();

protected:
	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	FName WeaponTopName;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	FName WeaponEndName;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool IsCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int ComboIdx;

	TQueue<int> AttackQueue;

	UPROPERTY()
	FTimerHandle AttackTimer;

	UPROPERTY()
	TSet<AActor*> VictimSet;
	
	UPROPERTY()
	EElement Element;

protected:
	virtual void Active() override;

	UFUNCTION()
	void FlushQueue();

public:
	UFUNCTION()
	FVector GetWeponTopPos();

	UFUNCTION()
	FVector GetWeponEndPos();

	UFUNCTION()
	void PlayCombo();

	UFUNCTION()
	void BeginSeinsing();	
	
	UFUNCTION()
	void EndSeinsing();

	UFUNCTION()
	void DamageToVictim();
};
