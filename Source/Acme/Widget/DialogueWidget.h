// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UTextBlock* TxtName;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UTextBlock* TxtDescription;	
	
	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UButton* BtnAccept;

	UPROPERTY(VisibleAnyWhere, meta = (BindWidget))
	class UButton* BtnReject;

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnHoveredAccept();

	UFUNCTION()
	void OnLeavedAccept();	
	
	UFUNCTION()
	void OnHoveredReject();

	UFUNCTION()
	void OnLeavedReject();

	UFUNCTION()
	void OnClickedAccept();

	UFUNCTION()
	void OnClickedReject();
	
protected:
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimHoverAccept;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimHoverReject;

	UPROPERTY()
	class AAcmeCharacter* Player;

	UPROPERTY()
	FQuest Quest;
	
public:
	UFUNCTION()
	void SetQuestInfo(FQuest newQuest);
};
