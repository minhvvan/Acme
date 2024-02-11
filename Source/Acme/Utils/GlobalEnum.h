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
enum class EMonsterState : uint8
{
	E_Attacked UMETA(DisplayName = "Attacked"),
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
	E_Lava UMETA(DisplayName = "Lava"),
	E_Energy UMETA(DisplayName = "Energy"),
	E_Plasma UMETA(DisplayName = "Plasma"),
	E_Stone UMETA(DisplayName = "Stone"),
	E_Metal UMETA(DisplayName = "Metal"),
	E_Sand UMETA(DisplayName = "Sand"),
	E_Glass UMETA(DisplayName = "Glass"),
	E_Tree UMETA(DisplayName = "Tree"),
	E_Coal UMETA(DisplayName = "Coal"),
	E_Steam UMETA(DisplayName = "Steam"),
	E_Swamp UMETA(DisplayName = "Swamp"),
	E_QuickSilver UMETA(DisplayName = "QuickSilver"),
	E_Wood UMETA(DisplayName = "Wood"),
	E_Boat UMETA(DisplayName = "Boat"),
	E_Storm UMETA(DisplayName = "Storm"),
	E_Seed UMETA(DisplayName = "Seed"),

	E_Sword UMETA(DisplayName = "Sword"),
	E_Helmet UMETA(DisplayName = "Helmet"),
	E_LetherArmor UMETA(DisplayName = "LetherArmor"),

	E_Empty UMETA(DisplayName = "Empty"),
};

UENUM(BlueprintType)
enum class EEquipmentPart : uint8
{
	E_Head UMETA(DisplayName = "Head"),
	E_Body UMETA(DisplayName = "Body"),
	E_Accessory UMETA(DisplayName = "Accessory"),

	E_None UMETA(DisplayName = "None"),
};


UENUM(BlueprintType)
enum class ESocketName : uint8
{
	E_HeadSocket UMETA(DisplayName = "HeadSocket"),
	E_BodyScoekt UMETA(DisplayName = "BodySocket"),
	E_HandScoekt UMETA(DisplayName = "HandScoekt"),
	E_BackScoekt UMETA(DisplayName = "BackScoekt"),

	E_End UMETA(DisplayName = "End"),
};


UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	E_Element UMETA(DisplayName = "Element"),
	E_Equipment UMETA(DisplayName = "Weapon"),
	E_Tool UMETA(DisplayName = "Armor"),
	E_Potion UMETA(DisplayName = "Potion"),
	E_Food UMETA(DisplayName = "Food"),
	E_Material UMETA(DisplayName = "Material"),
	E_End UMETA(DisplayName = "End"),
};
ENUM_RANGE_BY_COUNT(EItemCategory, EItemCategory::E_End);


UENUM(BlueprintType)
enum class EDetailAction : uint8
{
	E_Equip UMETA(DisplayName = "Equip"),
	E_Unequip UMETA(DisplayName = "Unequip"),
	E_Install UMETA(DisplayName = "Install"),
	E_Consume UMETA(DisplayName = "Consume"),
	E_Dump UMETA(DisplayName = "Dump"),
	E_End UMETA(DisplayName = "End"),
};


class ACME_API GlobalEnum
{
public:
	GlobalEnum();
	~GlobalEnum();
};
