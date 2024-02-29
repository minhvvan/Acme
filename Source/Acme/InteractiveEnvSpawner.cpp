// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveEnvSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Acme/Item/InteractiveItem.h"
#include "Acme/Utils/GlobalConst.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"
#include "Landscape.h"

AInteractiveEnvSpawner::AInteractiveEnvSpawner()
{
}

void AInteractiveEnvSpawner::Respawn()
{
	if (Enves.Num() == MaxPopulation) return;
	if (!Area) return;
	if (!EnvClass) return;

	FVector Loc = GetActorLocation();
	FVector Extand = Area->GetScaledBoxExtent();

	int TryNum = 0;
	
	while (Enves.Num() != MaxPopulation && TryNum <= MaxPopulation * 2)
	{
		FVector Pos = UKismetMathLibrary::RandomPointInBoundingBox(Loc, Extand);
		Pos.Z += 100;

		FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Pos, Pos + FVector(0, 0, -2000), ECollisionChannel::ECC_Visibility))
		{
			FVector newPos = HitResult.ImpactPoint;
			newPos.Z += 10;

			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			AInteractiveItem* Env = GetWorld()->SpawnActor<AInteractiveItem>(EnvClass, FTransform(FRotator::ZeroRotator, newPos), SpawnParam);

			if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
			FItem item = GameInstance->GetItemInfo(ItemName);

			Env->Init(item);
			Enves.Add(Env);
		}
		TryNum++;
	}
}

void AInteractiveEnvSpawner::BeginPlay()
{
	Respawn();
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &AInteractiveEnvSpawner::Respawn, RespawnInterval, true);
}

