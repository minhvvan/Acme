// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Item/TotemItem.h"
#include "Acme/Turret/Turret.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"
#include "Acme/Totem/Totem.h"
#include "DrawDebugHelpers.h"


void ATotemItem::Active()
{
	Super::Active();

	//Turret Spawn
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	FVector  Loc = Player->GetActorLocation();
	Loc += Player->GetActorForwardVector() * 50;
	Loc.Z += 100;

	FVector EndLoc = Loc;
	EndLoc.Z -= 500;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Loc, EndLoc, ECollisionChannel::ECC_Visibility))
	{
		FVector SpawnLocation = HitResult.ImpactPoint;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ATotem>(SpawnParams);
		GetWorld()->SpawnActor<ATotem>(TotemClass, SpawnLocation, Player->GetActorForwardVector().Rotation(), SpawnParams);

		Player->ConsumeItemQuick();
	}
}

void ATotemItem::AttachBack()
{
	AAcmeCharacter* Character = Cast<AAcmeCharacter>(GetOwner());
	if (!Character) return;

	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GameInstance->GetSocketName(ESocketName::E_BackSocket).SocketName);
	Mesh->SetVisibility(false);
}
