// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/QuestEntryWidget.h"
#include "Components/TextBlock.h"
#include "Acme/Data/QuestData.h"

void UQuestEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UQuestData* Data = Cast<UQuestData>(ListItemObject);
	if (!Data) return;

	FQuest quest = Data->Quest;
	TxtQuestTitle->SetText(FText::FromString(quest.Title));
}
