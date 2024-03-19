// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Utils/GlobalStruct.h"
#include "RewardDialogueWidget.generated.h"


/**
 * 
 */


UCLASS()
class ACME_API URewardDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnAccept;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtDescription;

	UPROPERTY(meta = (BindWidget))
	class UListView* LVReward;	
	
	UPROPERTY(meta = (BindWidget))
	class UListView* LVRequest;

protected:
	virtual void NativeOnInitialized();

	UFUNCTION()
	void OnClicked();

public:
	UFUNCTION()
	void SetQuestInfo(FQuest quest);

protected:
	UPROPERTY()
	FQuest QuestInfo;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY(EditAnywhere)
	USoundBase* RewardSFX;
};
