// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/RewardDialogueWidget.h"
#include "Acme/Data/ItemData.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/NPCCharacter.h"

void URewardDialogueWidget::NativeOnInitialized()
{
	BtnAccept->OnClicked.AddDynamic(this, &URewardDialogueWidget::OnClicked);
}

void URewardDialogueWidget::OnClicked()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayer()->GetPawn());

	for (FItem request : QuestInfo.Request)
	{
		Player->SubmitItem(request);
	}

	for (FItem reward : QuestInfo.Rewards)
	{
		for (int i = 0; i < reward.Num; i++)
		{
			Player->AddItem(reward);
		}
	}

	GetOwningPlayer()->bShowMouseCursor = false;
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly());

	RemoveFromParent();
}

void URewardDialogueWidget::SetQuestInfo(FQuest quest)
{
	QuestInfo = quest;

	TxtName->SetText(FText::FromString(QuestInfo.Client->GetNPCName()));
	TxtDescription->SetText(FText::FromString(QuestInfo.Desc));

	auto Rewards = QuestInfo.Rewards;
	auto Requests = QuestInfo.Request;

	for (FItem request : Requests)
	{
		UItemData* Data = NewObject<UItemData>();

		Data->SetItem(request);
		LVRequest->AddItem(Data);
	}

	for (FItem reward : Rewards)
	{
		UItemData* Data = NewObject<UItemData>();

		Data->SetItem(reward);
		LVReward->AddItem(Data);
	}
}
