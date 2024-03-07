// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalStruct.h"
#include "Acme/Utils/GlobalEnum.h"
#include "AlchemySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UAlchemySlotWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderItem;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgItem;

protected:
	UPROPERTY(VisibleAnywhere)
	FItem ItemInfo;

	UPROPERTY(VisibleAnywhere)
	int ItemIndex;

	UPROPERTY(VisibleAnywhere)
	class AAcmeCharacter* Player;

	UPROPERTY(VisibleAnywhere)
	class UAcmeGameInstance* GameInstance;

protected:
	UFUNCTION()
	void SetImage();

public:
	UFUNCTION()
	void SetSlot(FItem info, int idx);

	UFUNCTION()
	void Compose();

	UFUNCTION()
	bool IsEmpty();

	UFUNCTION()
	FItem GetItemInfo();

	UFUNCTION()
	void SetEmpty();

	UFUNCTION()
	bool IsSame(FItem item, int idx);

protected:
};
