// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItem.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/GlobalConst.h"
#include "Acme/Utils/Util.h"

void AEquipmentItem::Init(FItem newItem)
{
	ItemInfo = newItem;
}

void AEquipmentItem::AttachToSocket(EEquipmentPart ItemPart)
{
	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	FSocketString Socket = GameInstance->GetSocketName(ESocketName::E_End);
	switch (ItemPart)
	{
	case EEquipmentPart::E_Head:
		Socket = GameInstance->GetSocketName(ESocketName::E_HeadSocket);
		break;
	case EEquipmentPart::E_Body:
		Socket = GameInstance->GetSocketName(ESocketName::E_BodySocket);
		break;
	case EEquipmentPart::E_Hand:
		Socket = GameInstance->GetSocketName(ESocketName::E_HandSocket);
		break;
	}

	if(!Player) Player = Cast<AAcmeCharacter>(GetOwner());
	Mesh->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket.SocketName);
}

void AEquipmentItem::AttachBack()
{
	AAcmeCharacter* Character = Cast<AAcmeCharacter>(GetOwner());
	if (!Character) return;

	Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GlobalConst::BackSocket);
}

void AEquipmentItem::SetPart(EEquipmentPart newPart)
{
	Part = newPart;
}

UStaticMeshComponent* AEquipmentItem::GetMesh()
{
	return Mesh;
}

FItem& AEquipmentItem::GetItem()
{
	return ItemInfo;
}

int AEquipmentItem::GetArmorPower()
{
	return ItemInfo.ItemStat.Defence;
}
