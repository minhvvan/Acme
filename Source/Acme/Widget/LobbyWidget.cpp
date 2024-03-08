// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/LobbyWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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
}

void ULobbyWidget::OnContinueClicked()
{
	//Show SaveGame
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
