// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItem.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"

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
		Socket = GameInstance->GetSocketName(ESocketName::E_BodyScoekt);
		break;
	case EEquipmentPart::E_Shoe:
		Socket = GameInstance->GetSocketName(ESocketName::E_ShoeScoekt);
		break;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Socket: %s"), *Socket.SocketName.ToString()));


	if(!Player) Player = Cast<AAcmeCharacter>(GetOwner());
	Mesh->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket.SocketName);
}

void AEquipmentItem::SetPart(EEquipmentPart newPart)
{
	Part = newPart;
}
