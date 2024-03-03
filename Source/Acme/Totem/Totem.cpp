// Fill out your copyright notice in the Description page of Project Settings.


#include "Totem.h"
#include "Acme/Utils/Util.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/AcmeCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATotem::ATotem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(TEXT("/Script/Engine.StaticMesh'/Game/Acme/Meshes/Totem/Totem_low.Totem_low'"));
	if (MESH.Succeeded())
	{
		Mesh->SetStaticMesh(MESH.Object);
	}

	ConstructorHelpers::FObjectFinder<USoundBase> SFX(TEXT("/Script/Engine.SoundWave'/Game/Acme/SFX/SFX_Heal.SFX_Heal'"));
	if (SFX.Succeeded())
	{
		HealSFX = SFX.Object;
	}

	Interval = 3.f;
	Range = 500;
	Time = 60.f;
}

// Called when the game starts or when spawned
void ATotem::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimer, FTimerDelegate::CreateLambda([this]
		{
			Destroy();
		}), Time, false);

	GetWorldTimerManager().SetTimer(HealTimer, FTimerDelegate::CreateLambda([this]
		{
			Heal();
		}), Interval, true);
}

void ATotem::Heal()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), Range, 10, FColor::Red, false, 2.f, 0.f, 1.f);

	TArray<FOverlapResult> OverlapResults;
	
	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(Range));

	if (HealSFX)
	{
		AudioComp->SetSound(HealSFX);

		if (AudioComp->IsPlaying()) AudioComp->Stop();
		AudioComp->Play();
	}

	if (bResult)
	{
		for (auto Result : OverlapResults)
		{
			AAcmeCharacter* Player = Cast<AAcmeCharacter>(Result.GetActor());
			if (!Player) continue;

			Player->Heal(5);
			return;
		}
	}
}

// Called every frame
void ATotem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

