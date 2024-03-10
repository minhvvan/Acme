// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "QuestNotCompleteWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UQuestNotCompleteWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtDescription;	
	
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnAccept;

public:
	UFUNCTION()
	void SetQuestInfo(FQuest quest);

protected:
	UPROPERTY()
	FQuest QuestInfo;

	virtual void NativeOnInitialized();

	UFUNCTION()
	void OnClicked();
};
