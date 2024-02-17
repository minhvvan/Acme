// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "RewardEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API URewardEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* ImgItem;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtNum;

	UPROPERTY()
	class UAcmeGameInstance* GameInstance;

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

};
