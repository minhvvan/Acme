// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Acme/Utils/GlobalStruct.h"
#include "EquipmentComponent.generated.h"

class AActor_Weapon;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor_Weapon> CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor_Weapon> WeaponClass;
		
	UPROPERTY()
	class AAcmeCharacter* Player;

public:
	UFUNCTION()
	void EquipCurrentWeapon();

	UFUNCTION()
	void DismantleCurrentWeapon();

	UFUNCTION()
	AActor_Weapon* GetCurrentWeapon();

	UFUNCTION()
	void SetCurrentWeapon(FItem item);

};
