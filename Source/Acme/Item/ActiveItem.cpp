// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Item/ActiveItem.h"
#include "Kismet/GameplayStatics.h"

void AActiveItem::Active()
{
	if (ActiveSFX) UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ActiveSFX, GetActorLocation());
}
