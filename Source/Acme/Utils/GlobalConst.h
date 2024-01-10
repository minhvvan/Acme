// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class ACME_API GlobalConst
{
public:
	GlobalConst();
	~GlobalConst();

	static const FString FireElementName;
	static const FString WaterElementName;
	static const FString EarthElementName;
	static const FString AirElementName;
	static const FString IceElementName;
	static const FString ThunderElementName;

	static const FString EquipActionName;
	static const FString DismantleActionName;
	static const FString InstallActionName;
	static const FString ConsumeActionName;
	static const FString DumpActionName;
};
