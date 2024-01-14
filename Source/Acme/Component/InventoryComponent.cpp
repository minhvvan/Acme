// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Component/InventoryComponent.h"
#include "Acme/Utils/Util.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Actor_Weapon.h"
#include "Acme/InteractiveItem.h"
#include "Acme/AcmeCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	maxQuantity = 30;

	for (auto category : TEnumRange<EItemCategory>())
	{
		FItemList List = FItemList();
		List.SetNum(30, category);

		Items.Add({ category, List });
	}

	for (int i = 0; i < 8; i++)
	{
		FItem item = FItem();
		QuickSlots.Add(item);
	}
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItem(FItem newItem)
{
	if (newItem.Category == EItemCategory::E_End || newItem.Name == EItemName::E_Empty) return false;
	TArray<FItem>& ItemList = Items[newItem.Category].Get();

	//find
	bool bCanAdd = false;
	for (auto& Item : ItemList)
	{
		if (Item.Name == newItem.Name)
		{
			if (Item.Num < maxQuantity)
			{
				Item.Num++;
				bCanAdd = true;
				
				return true;
			}
		}
	}

	if (!bCanAdd)
	{
		for (auto& Item : ItemList)
		{
			if (Item.Name == EItemName::E_Empty)
			{
				Item.Name = newItem.Name;
				Item.Num = newItem.Num;
				Item.Equiped = newItem.Equiped;
				Item.Category = newItem.Category;

				return true;
			}
		}
	}

	return false;
}

FItemList& UInventoryComponent::GetItemList(EItemCategory category)
{
	//TODO: 예외처리해야 되는데....
	return Items[category];
}

FItem UInventoryComponent::GetItem(EItemCategory category, int idx)
{
	return Items[category].Get()[idx];
}

int UInventoryComponent::GetMaxQuantity()
{
	return maxQuantity;
}

void UInventoryComponent::MoveItems(EItemCategory Category, int from, int to)
{
	TArray<FItem>& ItemList = Items[Category].Get();

	if (ItemList[to].Name == ItemList[from].Name)
	{
		int movableAmount = maxQuantity - ItemList[to].Num;
		int moveAmount = movableAmount < ItemList[from].Num ? movableAmount : ItemList[from].Num;

		ItemList[from].Num -= moveAmount;
		if (ItemList[from].Num <= 0)
		{
			SetEmpty(ItemList[from]);
		}

		ItemList[to].Num += moveAmount;
	}
	else
	{
		FItem temp = ItemList[to];
		ItemList[to].Name = ItemList[from].Name;
		ItemList[to].Num = ItemList[from].Num;
		ItemList[to].Equiped = ItemList[from].Equiped;

		ItemList[from] = temp;
	}

	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());
	
	Player->UpdateInventoryWidget();
}

void UInventoryComponent::SetEmpty(FItem& item)
{
	item.Equiped = false;
	item.Name = EItemName::E_Empty;
	item.Num = 0;
}

TArray<FItem>& UInventoryComponent::GetQuickSlots()
{
	return QuickSlots;
}

void UInventoryComponent::SetQuickSlot(FItem item, int idx)
{
	QuickSlots[idx] = item;
}

void UInventoryComponent::Equip(int idx)
{
	TArray<FItem>& ItemList = Items[EItemCategory::E_Equipment].Get();
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	FItem& Item = ItemList[idx];
	if (Item.Name == EItemName::E_Empty) return;

	Item.Equiped = true;
	Player->SetWeapon(Item);
}

void UInventoryComponent::Unequip(int idx)
{
	TArray<FItem>& ItemList = Items[EItemCategory::E_Equipment].Get();
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	FItem& Item = ItemList[idx];
	if (Item.Equiped == false) return;

	Item.Equiped = false;
	Player->RemoveWeapon();
}

void UInventoryComponent::Dump(EItemCategory Category, int idx)
{
	TArray<FItem>& ItemList = Items[Category].Get();
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	FItem& Item = ItemList[idx];

	TSubclassOf<AInteractiveItem> SpawnClass = ItemClass[Item.Name];
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	FRotator rotator;
	FVector  SpawnLocation = Player->GetActorLocation() + Player->GetActorForwardVector() * 100;

	if (!SpawnClass) return;
	auto DropItem = GetWorld()->SpawnActor<AInteractiveItem>(SpawnClass, SpawnLocation, rotator, SpawnParams);
	DropItem->GetMesh()->SetSimulatePhysics(true);
	DropItem->Init(Item.Name, Item.Category);

	SetEmpty(Item);
}
