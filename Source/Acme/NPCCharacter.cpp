// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "AcmeGameInstance.h"

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
	
	QuestIndicator->SetVisibility(false);
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

	//TODO: Update Indicator;
}

void ANPCCharacter::RemoveQuset(int qusetID)
{
	for (int i = 0; i < QuestList.Num(); i++)
	{
		FQuest quest = QuestList[i];
		if (quest.QusetID == qusetID)
		{
			QuestList.RemoveAt(i);
			//TODO: Update Indicator;

			return;
		}
	}
}

