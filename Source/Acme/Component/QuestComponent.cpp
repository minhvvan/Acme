// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Component/QuestComponent.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/NPCCharacter.h"
#include "Acme/Utils/Util.h"

// Sets default values for this component's properties
UQuestComponent::UQuestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestComponent::AddQuest(FQuest newQuest)
{
	OngoingQuests.Add(newQuest);
	UpdateQuestState();
}

void UQuestComponent::CompleteQuest(int idx)
{
	FQuest quest = OngoingQuests[idx];
	OngoingQuests.RemoveAt(idx);
	quest.Client->CompleteQuest();

	CompletedQuests.Add(quest);
}

void UQuestComponent::RewardQuest(int questID)
{
	for (int i = 0; i < OngoingQuests.Num(); i++)
	{
		if (CompletedQuests[i].QusetID == questID)
		{
			FQuest quest = CompletedQuests[i];
			CompletedQuests.RemoveAt(i);

			if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());
			for (FItem reward : quest.Rewards)
			{
				Player->AddItem(reward);
			}
		}
	}
}

void UQuestComponent::UpdateQuestState()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());
	for (int i = 0; i < OngoingQuests.Num(); i++)
	{
		if (Player->IsCompleteQuest(OngoingQuests[i]))
		{
			CompleteQuest(i);
		}
	}
}

