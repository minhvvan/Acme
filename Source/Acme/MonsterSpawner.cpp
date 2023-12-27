// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "CharacterMonster.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxPopulation = 10;
	RespawnInterval = 30.f;
}

void AMonsterSpawner::Respawn()
{
	if (Monsters.Num() == MaxPopulation) return;
	if (!Area) return;

	while (Monsters.Num() != MaxPopulation)
	{
		//Spawn
		FVector Loc = GetActorLocation();
		FVector Extand = Area->GetScaledBoxExtent();

		FVector Pos = UKismetMathLibrary::RandomPointInBoundingBox(Loc, Extand);

		Pos.Z += 100;

		FHitResult Result;
		if (GetWorld()->LineTraceSingleByChannel(Result, Pos, Pos - (0, 0, 1000), ECollisionChannel::ECC_Visibility))
		{
			FVector SpawnPos = Result.Location;

			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			ACharacterMonster* Monster = GetWorld()->SpawnActor<ACharacterMonster>(MonsterClass, FTransform(FRotator::ZeroRotator, Pos), SpawnParam);
			
			Monster->OnDied.AddLambda([this, Monster]() { Monsters.Remove(Monster); });
			Monsters.Add(Monster);
		}
	}
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	Respawn();
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &AMonsterSpawner::Respawn, RespawnInterval, true);
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

