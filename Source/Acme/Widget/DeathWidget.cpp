// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/DeathWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

void UDeathWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnReplay->OnClicked.AddDynamic(this, &UDeathWidget::OnReplayClicked);
	BtnExit->OnClicked.AddDynamic(this, &UDeathWidget::OnExitClicked);
}

void UDeathWidget::OnReplayClicked()
{
	auto PC = GetOwningPlayer();
	if (!PC) return;
	Cast<AAcmeCharacter>(GetOwningPlayerPawn())->RespawnCharacter();

	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;

	RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UDeathWidget::OnExitClicked()
{
	//lobby·Î 
	

}
