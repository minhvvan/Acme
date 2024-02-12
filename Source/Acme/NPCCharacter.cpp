// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "AcmeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "AcmeCharacter.h"
#include "Acme/Utils/Util.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Indicator"));
	QuestIndicator->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//TODO: Update Quest
	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
	TArray<FQuest> Quests = GameInstance->GetQuest();

	for (auto quest : Quests)
	{
		QuestList.Add(quest);
	}

	UpdateQuestIndicator();
}	

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCCharacter::AddQuset(FQuest quest)
{
	QuestList.Add(quest);

	UpdateQuestIndicator();
}

void ANPCCharacter::RemoveQuset(int qusetID)
{
	for (int i = 0; i < QuestList.Num(); i++)
	{
		FQuest quest = QuestList[i];
		if (quest.QusetID == qusetID)
		{
			QuestList.RemoveAt(i);
			UpdateQuestIndicator();

			return;
		}
	}
}

void ANPCCharacter::UpdateQuestIndicator()
{
	if (QuestList.Num() == 0)
	{
		QuestIndicator->SetVisibility(false);
	}
	else
	{
		QuestIndicator->SetVisibility(true);

		if (!Player) Player = Cast<AAcmeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		
		for (auto quest : QuestList)
		{
			if (Player->IsCompleteQuest(quest))
			{
				QuestIndicator->SetStaticMesh(Meshes[EQuestState::E_Complete]);
				return;
			}
		}

		QuestIndicator->SetStaticMesh(Meshes[EQuestState::E_Ready]);
	}
}

