// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Acme/AcmeGameInstance.h"
#include "QuestData.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UQuestData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FQuest Quest;
};
