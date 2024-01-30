// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Component/EquipmentComponent.h"
#include "Acme/Actor_Weapon.h"
#include "Acme/AcmeCharacter.h"
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
	QuickSlotItems.Reserve(8);
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

	if (QuickSlotItems[idx])
	{
		CurrentHand = QuickSlotItems[idx];
		CurrentHand->AttachHand();
	}
}

ADefaultItem* UEquipmentComponent::GetCurrentHand()
{
	return CurrentHand.Get();
}

void UEquipmentComponent::SpawnItem(FItem item)
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	//Spawn
	if (item.Name == EItemName::E_Sword)
	{
		//item.Equiped = true;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Player;
		FRotator rotator;
		FVector  SpawnLocation = Player->GetActorLocation();
		SpawnLocation.Z += 100;

		auto CurrentItem = GetWorld()->SpawnActor<AActor_Weapon>(ItemClass, SpawnLocation, rotator, SpawnParams);
		if (CurrentItem)
		{
			CurrentItem->AttachToActor(Player, FAttachmentTransformRules::SnapToTargetIncludingScale);
			CurrentItem->AttachBack();
		}
	}
}