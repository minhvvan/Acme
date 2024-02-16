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

	bValidQuest = false;
}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
	Quest = GameInstance->GetQuest();
	Quest.Client = this;

	bValidQuest = true;

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
	Quest = quest;
	Quest.Client = this;

	bValidQuest = true;
	UpdateQuestIndicator();
}

void ANPCCharacter::RemoveQuset()
{
	bValidQuest = false;
}

void ANPCCharacter::UpdateQuestIndicator()
{
	if(!bValidQuest) QuestIndicator->SetVisibility(false);
	else
	{
		QuestIndicator->SetStaticMesh(Meshes[EQuestState::E_Ready]);
		QuestIndicator->SetVisibility(true);
	}
}

void ANPCCharacter::CompleteQuest()
{
	QuestIndicator->SetStaticMesh(Meshes[EQuestState::E_Complete]);
	QuestIndicator->SetVisibility(true);
}

void ANPCCharacter::Interact()
{
	if (!Player) return;
	FVector PlayerLoc = Player->GetActorLocation();
	TargetRot = (PlayerLoc - GetActorLocation()).Rotation();

	Player->ShowDialogWidget(Quest);
	Player->OnAcceptQuest.AddUObject(this, &ANPCCharacter::OnAcceptQuest);
}

void ANPCCharacter::OnAcceptQuest(int questID)
{
	bValidQuest = false;
	UpdateQuestIndicator();
}
