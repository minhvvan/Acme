// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/PauseWidget.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"
#include "Acme/Framework/AcmeGameInstance.h"

void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnReplay->OnClicked.AddDynamic(this, &UPauseWidget::OnReplayClicked);
	BtnSave->OnClicked.AddDynamic(this, &UPauseWidget::OnSaveClicked);
	BtnExit->OnClicked.AddDynamic(this, &UPauseWidget::OnExitClicked);
	BtnOk->OnClicked.AddDynamic(this, &UPauseWidget::OnOkClicked);
}

FReply UPauseWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		auto PC = Cast<APlayerController>(GetOwningPlayer());

		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());

		RemoveFromParent();
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}

	return FReply::Handled();
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetKeyboardFocus();
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
	if(!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	AAcmeCharacter* Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	if (Player)
	{
		GameInstance->SaveGame(Player);

		if (SaveSFX) PlaySound(SaveSFX);
		BorderAlert->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPauseWidget::OnExitClicked()
{
	//to lobby
	Cast<AAcmeCharacter>(GetOwningPlayerPawn())->MoveToLobby();
}

void UPauseWidget::OnOkClicked()
{
	BorderAlert->SetVisibility(ESlateVisibility::Hidden);
}
