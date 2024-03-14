// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Item/PotionItem.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Utils/Util.h"

void APotionItem::Active()
{
	Super::Active();
	Player->ConsumeItemQuick();

	Player->Heal(10);
}

void APotionItem::AttachBack()
{
	AAcmeCharacter* Character = Cast<AAcmeCharacter>(GetOwner());
	if (!Character) return;

	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GameInstance->GetSocketName(ESocketName::E_BackSocket).SocketName);
	Mesh->SetVisibility(false);
}
