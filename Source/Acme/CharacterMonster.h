// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDie);

UCLASS()
class ACME_API ACharacterMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAC_Stat> StatCompoenent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> HPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UAI_Monster* AnimInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnAttacked(int damage);

	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

	FOnDie OnDied;

protected:
	UFUNCTION()
	void InitState();

	UFUNCTION()
	void Die();
};
