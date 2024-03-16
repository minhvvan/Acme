// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UDeathWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();


protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnReplay;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnExit;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAcmeCharacter> CharacterClass;

protected:
	UFUNCTION()
	void OnReplayClicked();

	UFUNCTION()
	void OnExitClicked();
};
