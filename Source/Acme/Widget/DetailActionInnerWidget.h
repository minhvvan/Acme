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

public:
	UFUNCTION()
	void Init(EDetailAction action);

	FOnClick DelegateOnClicked;
};
