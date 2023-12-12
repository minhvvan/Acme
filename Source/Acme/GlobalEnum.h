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



class ACME_API GlobalEnum
{
public:
	GlobalEnum();
	~GlobalEnum();
};
