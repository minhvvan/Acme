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
	bool AddItem(FItem newItem);

	UFUNCTION()
	FItemList& GetItemList(EItemCategory category);

	UFUNCTION()
	FItem GetItem(EItemCategory category, int idx);

	UFUNCTION()
	int GetMaxQuantity();

	UFUNCTION()
	void MoveItems(EItemCategory Category, int from, int to);

	UFUNCTION()
	void SetEmpty(FItem& item);

	UFUNCTION()
	TArray<FItem>& GetQuickSlots();

	UFUNCTION()
	void SetQuickSlot(FItem item, int idx);	
	
	UFUNCTION()
	void Dump(EItemCategory Category, int idx);

	UFUNCTION()
	void UseItem(EItemCategory Category, int idx);

private:
	UPROPERTY()
	TMap<EItemCategory, FItemList> Items;
		
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int maxQuantity;

	UPROPERTY()
	TArray<FItem> QuickSlots;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<EItemName, TSubclassOf<class AInteractiveItem>> ItemClass;
};
