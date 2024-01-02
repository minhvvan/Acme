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
	E_Normal UMETA(DisplayName = "Normal"),
};
ENUM_RANGE_BY_COUNT(EElement, EElement::E_Normal);


UENUM(BlueprintType)
enum class EItem : uint8
{
	E_Cube UMETA(DisplayName = "Cube"),
	E_SPhere UMETA(DisplayName = "Sphere"),
};

class ACME_API GlobalEnum
{
public:
	GlobalEnum();
	~GlobalEnum();
};
