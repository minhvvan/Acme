// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Component/InventoryComponent.h"
#include "Acme/Utils/Util.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Item/InteractiveItem.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Framework/AcmeGameInstance.h"

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

	ConstructorHelpers::FClassFinder<AInteractiveItem> DI(TEXT("/Script/Engine.Blueprint'/Game/Acme/BluePrint/BP_DropItem.BP_DropItem_C'"));
	if (DI.Succeeded())
	{
		DropItemClass = DI.Class;
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

FItemList& UInventoryComponent::GetItemList(EItemCategory category)
{
	//TODO: 예외처리해야 되는데....
	return Items[category];
}

FItem UInventoryComponent::GetItem(EItemCategory category, int idx)
{
	return Items[category].Get()[idx];
}

FItem UInventoryComponent::GetQuickItem(int idx)
{
	return QuickSlots[idx];
}

int UInventoryComponent::GetMaxQuantity()
{
	return maxQuantity;
}

void UInventoryComponent::SetEmpty(FItem& item)
{
	item.Name = EItemName::E_Empty;
	item.Num = 0;
}

TArray<FItem>& UInventoryComponent::GetQuickSlots()
{
	return QuickSlots;
}

void UInventoryComponent::Dump(EItemCategory Category, int idx)
{
	TArray<FItem>& ItemList = Items[Category].Get();
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	FItem& Item = ItemList[idx];

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.Owner = Player;
	FRotator rotator;
	FVector  SpawnLocation = Player->GetActorLocation() + Player->GetActorForwardVector() * 100;

	if (!GameInstance) GameInstance = GetWorld()->GetGameInstance<UAcmeGameInstance>();
	FItem temp = GameInstance->GetItemInfo(Item.Name);

	AInteractiveItem* DropItem = GetWorld()->SpawnActor<AInteractiveItem>(DropItemClass, SpawnLocation, rotator, SpawnParams);
	if (!DropItemClass) return;
	
	DropItem->Init(temp);
	SetEmpty(Item);
}

void UInventoryComponent::UseItem(EItemCategory Category, int idx, int amount)
{
	TArray<FItem>& ItemList = Items[Category].Get();
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	FItem& Item = ItemList[idx];

	Item.Num -= amount;
	if (Item.Num == 0) SetEmpty(Item);
}

void UInventoryComponent::SubmitItem(FItem item)
{
	TArray<FItem>& ItemList = Items[item.Category].Get();
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	int amount = item.Num;

	for (FItem& ownItem : ItemList)
	{
		if (ownItem.Name == item.Name)
		{
			ownItem.Num -= amount;
			if (ownItem.Num <= 0)
			{
				amount += ownItem.Num;
				SetEmpty(ownItem);
			}

			if (amount == 0) break;
		}
	}
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
				Item = newItem;
				return true;
			}
		}
	}

	return false;
}

void UInventoryComponent::AddToInven(FItem newItem, int idx)
{
	TArray<FItem>& ItemList = Items[newItem.Category].Get();
	ItemList[idx] = newItem;
}

void UInventoryComponent::RemoveFromInven(EItemCategory Category, int idx)
{
	if (Category == EItemCategory::E_End) return;

	TArray<FItem>& ItemList = Items[Category].Get();
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwner());

	FItem& Item = ItemList[idx];
	SetEmpty(Item);
}

void UInventoryComponent::AddToQuick(FItem newItem, int idx)
{
	QuickSlots[idx] = newItem;
}

void UInventoryComponent::RemoveFromQuick(int idx)
{
	QuickSlots[idx].Category = EItemCategory::E_End;
	QuickSlots[idx].Name = EItemName::E_Empty;
	QuickSlots[idx].Num = 0;
}

bool UInventoryComponent::HasItem(FItem item)
{
	bool Result = false;
	int Num = item.Num;

	for (EItemCategory Category : TEnumRange<EItemCategory>())
	{
		TArray<FItem> ItemList = Items[Category].Get();
		for (FItem OwnItem : ItemList)
		{
			if (OwnItem.Name == item.Name)
			{
				Num -= OwnItem.Num;
			}
		}
	}

	for (FItem OwnItem : QuickSlots)
	{
		if (OwnItem.Name == item.Name)
		{
			Num -= OwnItem.Num;
		}
	}

	return Num <= 0;
}

int UInventoryComponent::GetItemNums(FItem item)
{
	TArray<FItem>& ItemList = Items[item.Category].Get();

	int Cnt = 0;

	for (auto ownItem : ItemList)
	{
		if (item.Name == ownItem.Name)
		{
			Cnt += ownItem.Num;
		}
	}

	return Cnt;
}

void UInventoryComponent::ConsumeQuickSlot(int idx)
{
	QuickSlots[idx].Num--;

	if (QuickSlots[idx].Num == 0)
	{
		RemoveFromQuick(idx);
	}
}

TMap<EItemCategory, FItemList> UInventoryComponent::GetAllInventory()
{
	return Items;
}

void UInventoryComponent::InitInventory(TMap<EItemCategory, FItemList> inven)
{
	Items = inven;
}