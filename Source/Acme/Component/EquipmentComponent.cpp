// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Component/EquipmentComponent.h"
#include "Acme/Actor_Weapon.h"
#include "Acme/AcmeCharacter.h"

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

	// ...
	
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentComponent::EquipCurrentWeapon()
{
	CurrentWeapon->AttachHand();
}

void UEquipmentComponent::DismantleCurrentWeapon()
{
	CurrentWeapon->AttachBack();
}

AActor_Weapon* UEquipmentComponent::GetCurrentWeapon()
{
	return CurrentWeapon.Get();
}

void UEquipmentComponent::SetCurrentWeapon(FItem item)
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	//Spawn
	if (item.Name == EItemName::E_Sword)
	{
		item.Equiped = true;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Player;
		FRotator rotator;
		FVector  SpawnLocation = Player->GetActorLocation();
		SpawnLocation.Z += 100;

		CurrentWeapon = GetWorld()->SpawnActor<AActor_Weapon>(WeaponClass, SpawnLocation, rotator, SpawnParams);
		if (CurrentWeapon)
		{
			CurrentWeapon->AttachToActor(Player, FAttachmentTransformRules::SnapToTargetIncludingScale);
			CurrentWeapon->AttachBack();
		}
	}
}

void UEquipmentComponent::RemoveCurrentWeapon()
{
	CurrentWeapon->Destroy();
	CurrentWeapon = nullptr;
}
