// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Acme/Utils/GlobalContainer.h"
#include "Acme/Utils/GlobalEnum.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	FItemList& GetItemList(EItemCategory category);

	UFUNCTION()
	FItem GetItem(EItemCategory category, int idx);

	UFUNCTION()
	FItem GetQuickItem(int idx);

	UFUNCTION()
	int GetMaxQuantity();

	UFUNCTION()
	void SetEmpty(FItem& item);

	UFUNCTION()
	TArray<FItem>& GetQuickSlots();
	
	UFUNCTION()
	void Dump(EItemCategory Category, int idx);

	UFUNCTION()
	void UseItem(EItemCategory Category, int idx, int amount);	
	
	UFUNCTION()
	void SubmitItem(FItem item);

	UFUNCTION()
	bool AddItem(FItem newItem);

	UFUNCTION()
	void AddToInven(FItem newItem, int idx);

	UFUNCTION()
	void RemoveFromInven(EItemCategory Category, int idx);

	UFUNCTION()
	void AddToQuick(FItem newItem, int idx);

	UFUNCTION()
	void RemoveFromQuick(int idx);

	UFUNCTION()
	bool HasItem(FItem item);

	UFUNCTION()
	int GetItemNums(FItem item);

	UFUNCTION()
	void ConsumeQuickSlot(int idx);

	UFUNCTION()
	TMap<EItemCategory, FItemList> GetAllInventory();

	UFUNCTION()
	void InitInventory(TMap<EItemCategory, FItemList> inven);

private:
	UPROPERTY()
	TMap<EItemCategory, FItemList> Items;
		
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int maxQuantity;

	UPROPERTY(SaveGame)
	TArray<FItem> QuickSlots;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY(EditAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AInteractiveItem> DropItemClass;

	UPROPERTY()
	class UAcmeGameInstance* GameInstance;
};
