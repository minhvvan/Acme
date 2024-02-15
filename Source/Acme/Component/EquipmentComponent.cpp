// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Component/EquipmentComponent.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/Item/BaseItem.h"
#include "Acme/Utils/Util.h"
#include "Acme/Interface/UsableInterface.h"
#include "Acme/Item/EquipmentItem.h"
#include "Acme/Item/ActiveItem.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	QuickSlotItems.SetNum(8);
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentComponent::SetCurrentHand(int idx)
{
	if (CurrentHand) CurrentHand->AttachBack();
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	if (QuickSlotItems[idx] && !QuickSlotItems[idx]->IsPendingKill())
	{
		Player->SetAnimState(EAnimState::E_Equiped);

		CurrentHand = QuickSlotItems[idx];
		CurrentHand->AttachToSocket(EEquipmentPart::E_Hand);
	}
	else
	{
		Player->SetAnimState(EAnimState::E_Unarmed);
	}
}

void UEquipmentComponent::ClearCurrentHand()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());
	Player->SetAnimState(EAnimState::E_Unarmed);
	CurrentHand = nullptr;
}

AActiveItem* UEquipmentComponent::GetCurrentHand()
{
	return CurrentHand.Get();
}

void UEquipmentComponent::SpawnItem(FItem item, int idx)
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());
	if (!GameInstance) GameInstance = Player->GetGameInstance<UAcmeGameInstance>();

	TSubclassOf<AActiveItem> ItemClass;
	if (!(ItemClass = GameInstance->GetEquipItemClass(item.Name))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	FRotator rotator;
	FVector  SpawnLocation = Player->GetActorLocation();
	SpawnLocation.Z += 100;

	AActiveItem* CurrentItem = GetWorld()->SpawnActor<AActiveItem>(ItemClass, SpawnLocation, rotator, SpawnParams);
	if (CurrentItem)
	{
		CurrentItem->AttachToActor(Player, FAttachmentTransformRules::SnapToTargetIncludingScale);
		CurrentItem->AttachBack();
		CurrentItem->Init(item);

		Player->SetShowInvenCam(CurrentItem->GetMesh());
	}

	DestroyAttachActor(idx);
	QuickSlotItems[idx] = CurrentItem;
}

void UEquipmentComponent::Active(int idx)
{
	if (!QuickSlotItems[idx]) return;

	IUsableInterface* ActiveItem = Cast<IUsableInterface>(QuickSlotItems[idx]);
	if (ActiveItem) ActiveItem->Active();
}

void UEquipmentComponent::DestroyAttachActor(int idx)
{
	if (QuickSlotItems[idx])
	{
		QuickSlotItems[idx]->Destroy();
	}
}

void UEquipmentComponent::Equip(EEquipmentPart part, FItem item)
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());
	if (!GameInstance) GameInstance = Player->GetGameInstance<UAcmeGameInstance>();

	TSubclassOf<ABaseItem> ItemClass;
	if (!(ItemClass = GameInstance->GetEquipItemClass(item.Name))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	FRotator rotator;
	FVector  SpawnLocation = Player->GetActorLocation();
	SpawnLocation.Z += 100;

	AEquipmentItem* CurrentItem = GetWorld()->SpawnActor<AEquipmentItem>(ItemClass, SpawnLocation, rotator, SpawnParams);
	if (CurrentItem)
	{
		switch (part)
		{
		case EEquipmentPart::E_Head:
			EquipmentHead = CurrentItem;
			break;
		case EEquipmentPart::E_Body:
			EquipmentBody = CurrentItem;
			break;
		case EEquipmentPart::E_Accessory:
			EquipmentAcc = CurrentItem;
			break;
		}

		CurrentItem->AttachToSocket(part);
		Player->SetShowInvenCam(CurrentItem->GetMesh());
	}
}

void UEquipmentComponent::UnEquip(EEquipmentPart part)
{
	TObjectPtr<ABaseItem> CurrentPart;
	switch (part)
	{
	case EEquipmentPart::E_Head:
		CurrentPart = EquipmentHead;
		break;
	case EEquipmentPart::E_Body:
		CurrentPart = EquipmentBody;
		break;
	case EEquipmentPart::E_Accessory:
		CurrentPart = EquipmentAcc;
		break;
	}

	CurrentPart->Destroy();
	CurrentPart = nullptr;
}
