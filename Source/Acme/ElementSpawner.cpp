// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "InteractiveElement.h"
#include "Acme/Item/InteractiveItem.h"
#include "Acme/Utils/GlobalConst.h"
#include "Acme/Utils/Util.h"

AElementSpawner::AElementSpawner()
{

}

void AElementSpawner::Respawn()
{
	if (Elements.Num() == MaxPopulation) return;
	if (!Area) return;
	if (!ElementClass) return;

	while (Elements.Num() != MaxPopulation)
	{
		//Spawn
		FVector Loc = GetActorLocation();
		FVector Extand = Area->GetScaledBoxExtent();

		FVector Pos = UKismetMathLibrary::RandomPointInBoundingBox(Loc, Extand);

		Pos.Z += 100;

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AInteractiveItem* Element = GetWorld()->SpawnActor<AInteractiveItem>(ElementClass, FTransform(FRotator::ZeroRotator, Pos), SpawnParam);

		FItem item;
		item.Num = 1;
		item.Category = EItemCategory::E_Element;
		switch (ElementType)
		{
		case EElement::E_Fire:
			item.Name = EItemName::E_Fire;
			break;
		case EElement::E_Water:
			item.Name = EItemName::E_Water;
			break;
		case EElement::E_Earth:
			item.Name = EItemName::E_Earth;
			break;
		case EElement::E_Air:
			item.Name = EItemName::E_Air;
			break;
		case EElement::E_Ice:
			item.Name = EItemName::E_Ice;
			break;
		case EElement::E_Thunder:
			item.Name = EItemName::E_Thunder;
			break;
		}

		Element->Init(item);
		Elements.Add(Element);
	}
}

void AElementSpawner::BeginPlay()
{
	Respawn();
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &AElementSpawner::Respawn, RespawnInterval, true);
}
