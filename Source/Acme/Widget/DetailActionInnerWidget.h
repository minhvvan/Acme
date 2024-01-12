// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalEnum.h"
#include "DetailActionInnerWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClick);

UCLASS()
class ACME_API UDetailActionInnerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UButton* BtnAction;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtAction;

	UFUNCTION()
	void OnClicked();

	UPROPERTY()
	EDetailAction DetailAction;

	UPROPERTY()
	EItemCategory ItemCategory;

	UPROPERTY()
	int Index;

	UFUNCTION()
	void Equip();

	UFUNCTION()
	void Unequip();

	UFUNCTION()
	void Consume();

	UFUNCTION()
	void Dump();

	UPROPERTY()
	class AAcmeCharacter* Player;

public:
	UFUNCTION()
	void Init(EDetailAction action, EItemCategory category, int idx);

	FOnClick DelegateOnClicked;
};
