// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SaveGameEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API USaveGameEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtSlotName;	
	
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnSelect;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgTumbnail;

public:
	virtual void NativeOnInitialized();

	UFUNCTION()
	void SetSlotName(FString name);

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	void OnClicked();

protected:
	UPROPERTY()
	FString SlotName;
};
