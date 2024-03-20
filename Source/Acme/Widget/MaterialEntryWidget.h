// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "MaterialEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UMaterialEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UBorder* BorderHeader;	
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* BorderItem;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgItem;	
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtOwnNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtName;

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	bool GetbHasItem();

protected:
	UPROPERTY()
	bool bHasItem;


protected:
	UFUNCTION()
	void UpdateBorderState();
};
