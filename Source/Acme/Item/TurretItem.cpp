// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Item/TurretItem.h"
#include "Acme/Turret/Turret.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"

void ATurretItem::Active()
{
	//Turret Spawn
	if (!TurretClass) return;
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Player;
	//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector  Loc = Player->GetActorLocation();
	Loc += Player->GetActorForwardVector() * 100;

	Loc.Z += 100;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Loc, Loc - (0, 0, 1000), ECollisionChannel::ECC_Visibility))
	{
		FVector SpawnLocation = HitResult.ImpactPoint;
		GetWorld()->SpawnActor<ATurret>(TurretClass, SpawnLocation, Player->GetActorForwardVector().Rotation(), SpawnParams);
		//GetWorld()->SpawnActor<ATurret>(TurretClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

		Player->ConsumeItemQuick();
	}
}

void ATurretItem::AttachBack()
{
	AAcmeCharacter* Character = Cast<AAcmeCharacter>(GetOwner());
	if (!Character) return;

	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GameInstance->GetSocketName(ESocketName::E_BackSocket).SocketName);
	Mesh->SetVisibility(false);
}
