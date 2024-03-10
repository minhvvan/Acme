// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/QuestNotCompleteWidget.h"
#include "QuestNotCompleteWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Acme/NPCCharacter.h"
#include "Acme/Framework/AcmeGameInstance.h"


void UQuestNotCompleteWidget::SetQuestInfo(FQuest quest)
{
	QuestInfo = quest;

	TxtName->SetText(FText::FromString(QuestInfo.Client->GetNPCName()));

	UAcmeGameInstance* GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
	FString Desc = FString(TEXT(""));

	for (auto item : QuestInfo.Request)
	{
		FItemString name = GameInstance->GetItemString(item.Name);

		Desc += name.Name;
		Desc += TEXT(",");
	}

	Desc = Desc.Left(Desc.Len()-1);

	TxtDescription->SetText(FText::FromString(Desc));
}

void UQuestNotCompleteWidget::NativeOnInitialized()
{
	BtnAccept->OnClicked.AddDynamic(this, &UQuestNotCompleteWidget::OnClicked);
}

void UQuestNotCompleteWidget::OnClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	PC->bShowMouseCursor = false;
	PC->SetInputMode(FInputModeGameOnly());

	RemoveFromParent();
}
