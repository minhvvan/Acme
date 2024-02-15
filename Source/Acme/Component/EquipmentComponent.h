// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Acme/Utils/GlobalStruct.h"
#include "EquipmentComponent.generated.h"

class AEquipmentItem;
class AActiveItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACME_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	//Usable Actor로 바꿔야 할 듯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActiveItem> CurrentHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEquipmentItem> EquipmentHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEquipmentItem> EquipmentBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEquipmentItem> EquipmentAcc;


	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

public:
	UFUNCTION()
	void SetCurrentHand(int idx);

	UFUNCTION()
	void ClearCurrentHand();

	UFUNCTION()
	AActiveItem* GetCurrentHand();

	UFUNCTION()
	void SpawnItem(FItem item, int idx);

	UFUNCTION()
	void Active(int idx);	

	UFUNCTION()
	void DestroyAttachActor(int idx);

	UFUNCTION()
	void Equip(EEquipmentPart part, FItem item);

	UFUNCTION()
	void UnEquip(EEquipmentPart part);

private:
	UPROPERTY(VisibleAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TArray<class AActiveItem*> QuickSlotItems;
};
