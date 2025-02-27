// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/LobbyWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Framework/AcmeSaveGame.h"
#include "Acme/Framework/MasterSaveGame.h"
#include "Acme/Data/SaveGameData.h"

void ULobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnOk->OnClicked.AddDynamic(this, &ULobbyWidget::OnOkClicked);

	BtnNewGame->OnClicked.AddDynamic(this, &ULobbyWidget::OnNewGameClicked);
	BtnContinue->OnClicked.AddDynamic(this, &ULobbyWidget::OnContinueClicked);
	BtnExit->OnClicked.AddDynamic(this, &ULobbyWidget::OnExitClicked);

	BtnNewGame->OnHovered.AddDynamic(this, &ULobbyWidget::OnNewGameHovered);
	BtnContinue->OnHovered.AddDynamic(this, &ULobbyWidget::OnContinueHovered);
	BtnExit->OnHovered.AddDynamic(this, &ULobbyWidget::OnExitHovered);

	BtnNewGame->OnUnhovered.AddDynamic(this, &ULobbyWidget::OnNewGameLeaved);
	BtnContinue->OnUnhovered.AddDynamic(this, &ULobbyWidget::OnContinueLeaved);
	BtnExit->OnUnhovered.AddDynamic(this, &ULobbyWidget::OnExitLeaved);
}

void ULobbyWidget::OnNewGameClicked()
{
	//OpenLevel
	GetWorld()->SeamlessTravel(TEXT("Game"));
	auto PC = Cast<APlayerController>(GetOwningPlayer());
	if (!PC) return;

	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;
}

void ULobbyWidget::OnContinueClicked()
{
	UAcmeGameInstance* GameInstance = GetGameInstance<UAcmeGameInstance>();

	//Show SaveGame
	UMasterSaveGame* SaveGameList = Cast<UMasterSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveGameList"), 0));
	if (!SaveGameList)
	{
		BorderAlert->SetVisibility(ESlateVisibility::Visible);
		if(FailFoundSFX) PlaySound(FailFoundSFX);
		return;
	}

	LVSaveGame->ClearListItems();
	for (FString slotName : SaveGameList->SaveGames)
	{
		UAcmeSaveGame* SaveGame = Cast<UAcmeSaveGame>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
		UTexture2D* thumbnail = GameInstance->ImportSaveThumbnail(slotName);
		if (!SaveGame) continue;

		USaveGameData* Data = NewObject<USaveGameData>();
		Data->SlotName = slotName;

		if (thumbnail)
		{
			Data->Thumbnail = thumbnail;
		}

		LVSaveGame->AddItem(Data);
	}
}

void ULobbyWidget::OnExitClicked()
{
	//End Game
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}

void ULobbyWidget::OnNewGameHovered()
{
	if (HoverNewGame)
	{
		PlayAnimation(HoverNewGame);
	}
}

void ULobbyWidget::OnNewGameLeaved()
{
	if (HoverNewGame)
	{
		PlayAnimationReverse(HoverNewGame);
	}
}

void ULobbyWidget::OnContinueHovered()
{
	if (HoverContinue)
	{
		PlayAnimation(HoverContinue);
	}
}

void ULobbyWidget::OnContinueLeaved()
{
	if (HoverContinue)
	{
		PlayAnimationReverse(HoverContinue);
	}
}

void ULobbyWidget::OnExitHovered()
{
	if (HoverExit)
	{
		PlayAnimation(HoverExit);
	}
}

void ULobbyWidget::OnExitLeaved()
{
	if (HoverExit)
	{
		PlayAnimationReverse(HoverExit);
	}
}

void ULobbyWidget::OnOkClicked()
{
	BorderAlert->SetVisibility(ESlateVisibility::Hidden);
}
