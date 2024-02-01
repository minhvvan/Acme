// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Component/EquipmentComponent.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/AcmeGameInstance.h"
#include "Acme/Actor_Weapon.h"
#include "Acme/DefaultItem.h"
#include "Acme/Utils/Util.h"

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

	if (QuickSlotItems[idx] && !QuickSlotItems[idx]->IsPendingKill())
	{
		if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());
		Player->SetAnimState(EAnimState::E_Equiped);

		CurrentHand = QuickSlotItems[idx];
		CurrentHand->AttachHand();
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

ADefaultItem* UEquipmentComponent::GetCurrentHand()
{
	return CurrentHand.Get();
}

void UEquipmentComponent::SpawnItem(FItem item, int idx)
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());
	if (!GameInstance) GameInstance = Player->GetGameInstance<UAcmeGameInstance>();

	TSubclassOf<ADefaultItem> ItemClass;
	if (!(ItemClass = GameInstance->GetItemClass(item.Name))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	FRotator rotator;
	FVector  SpawnLocation = Player->GetActorLocation();
	SpawnLocation.Z += 100;

	ADefaultItem* CurrentItem = GetWorld()->SpawnActor<ADefaultItem>(ItemClass, SpawnLocation, rotator, SpawnParams);
	if (CurrentItem)
	{
		CurrentItem->AttachToActor(Player, FAttachmentTransformRules::SnapToTargetIncludingScale);
		CurrentItem->AttachBack();
	}

	DestroyAttachActor(idx);
	QuickSlotItems[idx] = CurrentItem;
}

void UEquipmentComponent::Active(int idx)
{
	if (!QuickSlotItems[idx]) return;
	QuickSlotItems[idx]->Active();
}

void UEquipmentComponent::DestroyAttachActor(int idx)
{
	if (QuickSlotItems[idx])
	{
		QuickSlotItems[idx]->Destroy();
	}
}
