// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Util.generated.h"

UCLASS()
class ACME_API UUtil : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	static void DebugPrint(const FString& msg);
};
