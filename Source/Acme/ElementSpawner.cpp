// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "InteractiveElement.h"
#include "Acme/Utils/GlobalConst.h"

AElementSpawner::AElementSpawner()
{

}

void AElementSpawner::Respawn()
{
	if (Elements.Num() == MaxPopulation) return;
	if (!Area) return;

	while (Elements.Num() != MaxPopulation)
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

			AInteractiveElement* Element = GetWorld()->SpawnActor<AInteractiveElement>(ElementClass, FTransform(FRotator::ZeroRotator, Pos), SpawnParam);
			Element->SetElementType(ElementType);

			switch (ElementType)
			{
			case EElement::E_Fire:
				Element->SetName(GlobalConst::FireElementName);
				break;
			case EElement::E_Water:
				Element->SetName(GlobalConst::WaterElementName);
				break;
			case EElement::E_Earth:
				Element->SetName(GlobalConst::EarthElementName);
				break;
			case EElement::E_Air:
				Element->SetName(GlobalConst::AirElementName);
				break;
			case EElement::E_Ice:
				Element->SetName(GlobalConst::IceElementName);
				break;
			case EElement::E_Thunder:
				Element->SetName(GlobalConst::ThunderElementName);
				break;
			}

			Elements.Add(Element);
		}
	}
}

void AElementSpawner::BeginPlay()
{
	Respawn();
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &AElementSpawner::Respawn, RespawnInterval, true);
}
