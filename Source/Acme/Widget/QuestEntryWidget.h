// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "QuestEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UQuestEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtQuestTitle;

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

};
