// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
#include "DetailActionWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UDetailActionWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UVerticalBox* VertAction;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DetailInnerWidgetClass;

	UPROPERTY()
	FItem ItemInfo;

	UPROPERTY()
	int Index;

public:
	UFUNCTION()
	void SetInnerWidget(FItem& item, int idx);

	UFUNCTION()
	void CreateEquip();

	UFUNCTION()
	void CreateUnEquip();

	UFUNCTION()
	void CreateConsume();

	UFUNCTION()
	void CreateDump();

	UFUNCTION()
	void CreateInstall();

	UFUNCTION()
	void CloseWidget();
};
