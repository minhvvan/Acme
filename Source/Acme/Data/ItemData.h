// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Acme/Utils/GlobalStruct.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UUserWidget* ParentRef;

	UPROPERTY()
	FItem ItemInfo;

	UPROPERTY()
	int Index;

	UPROPERTY()
	bool bCanShowDetail;

	UFUNCTION()
	void SetItem(FItem info);

	UFUNCTION()
	FItem GetItemInfo();

	UFUNCTION()
	void SetIndex(int idx);

	UFUNCTION()
	int GetIndex();

	UFUNCTION()
	void SetbCanShowDetail(bool bShow);

	UFUNCTION()
	bool GetbCanShowDetail();

	UFUNCTION()
	void SetParentRef(UUserWidget* parent);

	UFUNCTION()
	UUserWidget* GetParentRef();
};
