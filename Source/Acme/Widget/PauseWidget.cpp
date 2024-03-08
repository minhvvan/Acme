// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Acme/AcmeCharacter.h"

void UPauseWidget::NativeOnInitialized()
{
	BtnReplay->OnClicked.AddDynamic(this, &UPauseWidget::OnReplayClicked);
	BtnSave->OnClicked.AddDynamic(this, &UPauseWidget::OnSaveClicked);
	BtnExit->OnClicked.AddDynamic(this, &UPauseWidget::OnExitClicked);
}

void UPauseWidget::OnReplayClicked()
{
	auto PC = GetOwningPlayer();
	if (!PC) return;

	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;

	RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UPauseWidget::OnSaveClicked()
{
	//save
}

void UPauseWidget::OnExitClicked()
{
	//to lobby
	Cast<AAcmeCharacter>(GetOwningPlayerPawn())->MoveToLobby();
}
