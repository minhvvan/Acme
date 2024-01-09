// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAnimState : uint8 
{ 
	E_Unarmed UMETA(DisplayName = "Unarmed"), 
	E_Equiped UMETA(DisplayName = "Equiped"), 
};

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	E_Forward UMETA(DisplayName = "Forward"),
	E_Backward UMETA(DisplayName = "Backward"),
	E_Right UMETA(DisplayName = "Right"),
	E_Left UMETA(DisplayName = "Left"),
};

UENUM(BlueprintType)
enum class EElement : uint8
{
	E_Fire UMETA(DisplayName = "Fire"),
	E_Water UMETA(DisplayName = "Water"),
	E_Earth UMETA(DisplayName = "Earth"),
	E_Air UMETA(DisplayName = "Air"),
	E_Ice UMETA(DisplayName = "Ice"),
	E_Thunder UMETA(DisplayName = "Thunder"),
	E_End UMETA(DisplayName = "Normal"),
};
ENUM_RANGE_BY_COUNT(EElement, EElement::E_End);

UENUM(BlueprintType)
enum class EItemName : uint8
{
	E_Fire UMETA(DisplayName = "Fire"),
	E_Water UMETA(DisplayName = "Water"),
	E_Air UMETA(DisplayName = "Air"),
	E_Earth UMETA(DisplayName = "Earth"),
	E_Ice UMETA(DisplayName = "Ice"),
	E_Thunder UMETA(DisplayName = "Thunder"),
	E_Cube UMETA(DisplayName = "Cube"),
	E_SPhere UMETA(DisplayName = "Sphere"),
	E_Empty UMETA(DisplayName = "Empty"),
};

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	E_Element UMETA(DisplayName = "Element"),
	E_Weapon UMETA(DisplayName = "Weapon"),
	E_Armor UMETA(DisplayName = "Armor"),
	E_Potion UMETA(DisplayName = "Potion"),
	E_Food UMETA(DisplayName = "Food"),
	E_Material UMETA(DisplayName = "Material"),
	E_End UMETA(DisplayName = "End"),
};
ENUM_RANGE_BY_COUNT(EItemCategory, EItemCategory::E_End);


class ACME_API GlobalEnum
{
public:
	GlobalEnum();
	~GlobalEnum();
};
