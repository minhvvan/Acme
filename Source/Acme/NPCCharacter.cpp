// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AcmeCharacter.h"
#include "Acme/Utils/Util.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestIndicator = ACharacter::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Indicator"));
	QuestIndicator->SetupAttachment(RootComponent);

	OverlapComp = ACharacter::CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(RootComponent);	
	
	InteractWidget = ACharacter::CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
	TArray<FQuest> Quests = GameInstance->GetQuest();

	for (FQuest quest : Quests)
	{
		QuestList.Add(quest);
	}

	UpdateQuestIndicator();
	InteractWidget->SetVisibility(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ANPCCharacter::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &ANPCCharacter::OnEndOverlap);
}

void ANPCCharacter::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AAcmeCharacter>(OtherActor);
	if (OtherActor != nullptr && OtherComp != nullptr && Player)
	{
		InteractWidget->SetVisibility(true);
	}
}

void ANPCCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		InteractWidget->SetVisibility(false);
		Player = nullptr;
	}
}


// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRot = GetActorRotation();
	if (TargetRot != CurrentRot)
	{
		FRotator Rot = FMath::Lerp(CurrentRot, TargetRot, .1);
		SetActorRotation(Rot);
	}
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

		if (!Player) Player = Cast<AAcmeCharacter>(UGameplayStatics::GetPlayerCharacter(ACharacter::GetWorld(), 0));
		
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

void ANPCCharacter::Interact()
{
	//TODO: Player쪽으로 방향 돌리고
	//WIdget 띄우기

	if (!Player) return;
	FVector PlayerLoc = Player->GetActorLocation();
	TargetRot = (PlayerLoc - GetActorLocation()).Rotation();

	Player->ShowDialogWidget();
}

