// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnNewGame;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnContinue;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnExit;	
	
	UPROPERTY(meta = (BindWidget))
	class UListView* LVSaveGame;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HoverNewGame;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HoverContinue;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HoverExit;

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnNewGameClicked();

	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnExitClicked();

	UFUNCTION()
	void OnNewGameHovered();

	UFUNCTION()
	void OnNewGameLeaved();

	UFUNCTION()
	void OnContinueHovered();

	UFUNCTION()
	void OnContinueLeaved();

	UFUNCTION()
	void OnExitHovered();

	UFUNCTION()
	void OnExitLeaved();
};
