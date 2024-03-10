// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/LobbyWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Acme/Framework/AcmeSaveGame.h"
#include "Acme/Framework/MasterSaveGame.h"

void ULobbyWidget::NativeOnInitialized()
{
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
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Game")));

	auto PC = Cast<APlayerController>(GetOwningPlayer());
	if (!PC) return;

	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;
}

void ULobbyWidget::OnContinueClicked()
{
	//Show SaveGame
	UMasterSaveGame* SaveGameList = Cast<UMasterSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveGameList"), 0));
	if (!SaveGameList)
	{
		//TODO: Alret: no games
		return;
	}

	for (FString slotName : SaveGameList->SaveGames)
	{
		UAcmeSaveGame* SaveGame = Cast<UAcmeSaveGame>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
		if (!SaveGame) continue;

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%s"), *slotName));
	}

	//LVSaveGame
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
