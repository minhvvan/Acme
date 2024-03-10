// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Item/TurretItem.h"
#include "Acme/Turret/Turret.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"

void ATurretItem::Active()
{
	//Turret Spawn
	if (!TurretClass) return;
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Player;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector Loc = Player->GetActorLocation();
	Loc += Player->GetActorForwardVector() * 50;
	Loc.Z += 100;

	FVector EndLoc = Loc;
	EndLoc.Z -= 500;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Loc, EndLoc, ECollisionChannel::ECC_Visibility))
	{
		FVector SpawnLocation = HitResult.ImpactPoint;
		GetWorld()->SpawnActor<ATurret>(TurretClass, SpawnLocation, Player->GetActorForwardVector().Rotation(), SpawnParams);

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
