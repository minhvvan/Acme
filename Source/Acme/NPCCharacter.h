// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

struct FQuest;

UCLASS()
class ACME_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();

protected:
	UPROPERTY(EditAnywhere, Category = Default)
	class UStaticMeshComponent* QuestIndicator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void AddQuset(FQuest quest);

	UFUNCTION()
	void RemoveQuset(int qusetID);


protected:
	UPROPERTY()
	TArray<FQuest> QuestList;
};
