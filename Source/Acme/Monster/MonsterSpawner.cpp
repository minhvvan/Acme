// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Debug/DebugDrawComponent.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxPopulation = 10;
	RespawnInterval = 30.f;

	//ConstructorHelpers::FClassFinder<ACharacterMonster> MON(TEXT("/Script/Engine.Blueprint'/Game/Acme/BluePrint/BP_Monster.BP_Monster_C'"));
	//if (MON.Succeeded())
	//{
	//	MonsterClass = MON.Class;
	//}
}

void AMonsterSpawner::Respawn()
{
	if (Monsters.Num() == MaxPopulation) return;
	if (!Area) return;
	if (!MonsterClass.Get()) return;

	//while (Monsters.Num() != MaxPopulation && TryNum <= MaxPopulation * 2)
	for(int i = 0; i < MaxPopulation; i++)
	{
		//Spawn
		FVector Loc = GetActorLocation();
		FVector Extand = Area->GetScaledBoxExtent();

		FVector Pos = UKismetMathLibrary::RandomPointInBoundingBox(Loc, Extand);

		FHitResult Result;
		//if (GetWorld()->LineTraceSingleByChannel(Result, Pos, Pos - (0, 0, 100), ECollisionChannel::ECC_Visibility))
		//{
			//FVector SpawnPos = Result.Location;

		if (MonsterClass)
		{
			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			ACharacterMonster* Monster = GetWorld()->SpawnActor<ACharacterMonster>(MonsterClass, Pos, FRotator::ZeroRotator, SpawnParam);
			//Monster->SetCenterPos(CenterPos);
			//Monster->OnDied.AddLambda([this, Monster]() { Monsters.Remove(Monster); });
			//Monsters.Add(Monster);
		}

		//}
	}
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

	CenterPos = GetActorLocation();
	
	//DrawDebugSphere(GetWorld(), CenterPos, 10, 10, FColor::Blue, false, 10.f);

	Respawn();
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &AMonsterSpawner::Respawn, RespawnInterval, true);
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

