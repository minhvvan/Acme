// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/SaveGameEntryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Acme/Data/SaveGameData.h"
#include "Acme/Framework/AcmeSaveGame.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USaveGameEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnSelect->OnClicked.AddDynamic(this, &USaveGameEntryWidget::OnClicked);
}

void USaveGameEntryWidget::SetSlotName(FString name)
{
	TxtSlotName->SetText(FText::FromString(name));
}

void USaveGameEntryWidget::SetThumbnail(UTexture2D* thumbnail)
{
	ImgTumbnail->SetBrushFromTexture(thumbnail);
}

void USaveGameEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	USaveGameData* Data = Cast<USaveGameData>(ListItemObject);
	SlotName = Data->SlotName;

	SetSlotName(SlotName);
	SetThumbnail(Data->Thumbnail);
}

void USaveGameEntryWidget::OnClicked()
{
	//SaveGame으로 설정해야 함
	UAcmeGameInstance* GameInstance = GetGameInstance<UAcmeGameInstance>();
	GameInstance->LoadGame(SlotName);
}