// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Item/FoodItem.h"
#include "Acme/Utils/Util.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Framework/AcmeGameInstance.h"

void AFoodItem::BeginPlay()
{
	//TODO: Data로 만들어야 함
	Satiety = 10;
}

void AFoodItem::Active()
{
	//TODO:Play Anim

	Player->ConsumeItemQuick();
	Player->AddSatiety(Satiety);
}

void AFoodItem::AttachBack()
{
	AAcmeCharacter* Character = Cast<AAcmeCharacter>(GetOwner());
	if (!Character) return;

	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GameInstance->GetSocketName(ESocketName::E_BackSocket).SocketName);
	Mesh->SetVisibility(false);
}
