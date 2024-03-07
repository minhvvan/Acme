// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePausedWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UGamePausedWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();


protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnReplay;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnExit;

protected:
	UFUNCTION()
	void OnReplayClicked();

	UFUNCTION()
	void OnExitClicked();
};
