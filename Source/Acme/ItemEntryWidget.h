// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GlobalEnum.h"
#include "ItemEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UItemEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgItem;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtAmount;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtX;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	UPROPERTY(EditAnywhere)
	TMap<EItemName, UTexture2D*> ItemImages;
};
