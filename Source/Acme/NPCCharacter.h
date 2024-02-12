// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Acme/Utils/GlobalEnum.h"
#include "AcmeGameInstance.h"
#include "InteractableActor.h"
#include "NPCCharacter.generated.h"

struct FQuest;

UCLASS()
class ACME_API ANPCCharacter : public ACharacter, public IInteractableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();

protected:
	UPROPERTY(EditAnywhere, Category = Default)
	class UStaticMeshComponent* QuestIndicator;

	UPROPERTY(VisibleAnywhere, Category = Default)
	class USphereComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = Default)
	class UWidgetComponent* InteractWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void AddQuset(FQuest quest);

	UFUNCTION()
	void RemoveQuset(int qusetID);

	UFUNCTION()
	void UpdateQuestIndicator();

	virtual void Interact() override;

protected:
	UPROPERTY()
	TArray<FQuest> QuestList;

	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY(EditAnywhere, Category = "Quest")
	TMap<EQuestState, class UStaticMesh*> Meshes;
};
