// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveEnvSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Acme/Item/InteractiveItem.h"
#include "Acme/Utils/GlobalConst.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"
#include "Landscape.h"
#include "DrawDebugHelpers.h"

AInteractiveEnvSpawner::AInteractiveEnvSpawner()
{
	//ConstructorHelpers::FClassFinder<AInteractiveItem> ENV(TEXT("/Script/Engine.Blueprint'/Game/Acme/BluePrint/BP_StaticItem.BP_StaticItem_C'"));
	//if (ENV.Succeeded())
	//{
	//	EnvClass = ENV.Class;
	//}
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
		Pos.Z += 500;

		FVector EndPos = Pos;
		EndPos.Z -= 1000;

		TArray<FHitResult> HitResult;
		if (GetWorld()->LineTraceMultiByChannel(HitResult, Pos, EndPos, ECollisionChannel::ECC_Visibility))
		{
			for (FHitResult result : HitResult)
			{
				if (result.GetActor()->ActorHasTag(FName(TEXT("Ground"))))
				{
					FVector newPos = result.ImpactPoint;
					newPos.Z += 10;

					FActorSpawnParameters SpawnParam;
					SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
					AInteractiveItem* Env = GetWorld()->SpawnActor<AInteractiveItem>(EnvClass, newPos, FRotator::ZeroRotator, SpawnParam);

					if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
					FItem item = GameInstance->GetItemInfo(ItemName);

					Env->Init(item);
					Env->OnInteract.AddUObject(this, &AInteractiveEnvSpawner::RemoveFromEnves);

					Enves.Add(Env);

					continue;
				}
			}
		}
		TryNum++;
	}
}

void AInteractiveEnvSpawner::RemoveFromEnves(AInteractiveItem* Destroyed)
{
	for (auto env : Enves)
	{
		if (env == Destroyed)
		{
			Enves.Remove(env);
			return;
		}
	}
}

void AInteractiveEnvSpawner::BeginPlay()
{
	Respawn();
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &AInteractiveEnvSpawner::Respawn, RespawnInterval, true);
}

