// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnReplay;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnSave;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnExit;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnOk;	
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* BorderAlert;

	UPROPERTY(EditAnywhere)
	USoundBase* SaveSFX;

protected:
	virtual void NativeOnInitialized();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

	virtual void NativeConstruct();

	UFUNCTION()
	void OnReplayClicked();

	UFUNCTION()
	void OnSaveClicked();

	UFUNCTION()
	void OnExitClicked();

	UFUNCTION()
	void OnOkClicked();

protected:
	UPROPERTY()
	class UAcmeGameInstance* GameInstance;
};
