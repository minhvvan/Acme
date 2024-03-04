// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Item/ActiveItem.h"
#include "SwordActor.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API ASwordActor : public AActiveItem
{
	GENERATED_BODY()

public:
	ASwordActor();

protected:
	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	FName WeaponTopName;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	FName WeaponEndName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool IsCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int ComboIdx;

	TQueue<int> AttackQueue;

	UPROPERTY()
	FTimerHandle AttackTimer;

	UPROPERTY()
	TSet<AActor*> VictimSet;
	
protected:
	UFUNCTION()
	void FlushQueue();

public:
	virtual void Active() override;

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
