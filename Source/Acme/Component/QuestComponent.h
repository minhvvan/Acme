// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "QuestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACME_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void AddQuest(FQuest newQuest);

	UFUNCTION()
	void CompleteQuest(int idx);

	UFUNCTION()
	void RewardQuest(int questID);

	UFUNCTION()
	void UpdateQuestState();

protected:
	UPROPERTY()
	TArray<FQuest> OngoingQuests;

	//완료했지만 보상을 받지않은 퀘스트
	UPROPERTY()
	TArray<FQuest> CompletedQuests;

	UPROPERTY()
	class AAcmeCharacter* Player;
};
