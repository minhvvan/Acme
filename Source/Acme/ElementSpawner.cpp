// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "InteractiveElement.h"
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

		AInteractiveElement* Element = GetWorld()->SpawnActor<AInteractiveElement>(ElementClass, FTransform(FRotator::ZeroRotator, Pos), SpawnParam);
		Element->SetElementType(ElementType);

		switch (ElementType)
		{
		case EElement::E_Fire:
			Element->SetName(EItemName::E_Fire);
			break;
		case EElement::E_Water:
			Element->SetName(EItemName::E_Water);
			break;
		case EElement::E_Earth:
			Element->SetName(EItemName::E_Earth);
			break;
		case EElement::E_Air:
			Element->SetName(EItemName::E_Air);
			break;
		case EElement::E_Ice:
			Element->SetName(EItemName::E_Ice);
			break;
		case EElement::E_Thunder:
			Element->SetName(EItemName::E_Thunder);
			break;
		}

		Elements.Add(Element);
	}
}

void AElementSpawner::BeginPlay()
{
	Respawn();
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &AElementSpawner::Respawn, RespawnInterval, true);
}
