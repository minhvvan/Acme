// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Component/InventoryComponent.h"
#include "Acme/Utils/Util.h"
#include "Acme/Utils/GlobalEnum.h"

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
		List.SetNum(30);

		Items.Add({ category, List});
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
	TArray<FItem>& ItemList = Items[newItem.Category].Get();

	//find
	bool bCanAdd = false;
	for (auto Item : ItemList)
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

FItemList UInventoryComponent::GetItemList(EItemCategory category)
{
	if (Items.Find(category))
	{
		return Items[category];
	}

	return FItemList();
}
