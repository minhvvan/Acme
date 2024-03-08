// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Lobby/LobbyPC.h"
#include "Acme/Widget/LobbyWidget.h"
#include "Acme/Utils/Util.h"


ALobbyPC::ALobbyPC()
{
	ConstructorHelpers::FClassFinder<ULobbyWidget> Lobby(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Acme/Widgets/WBP_LobbyWidget.WBP_LobbyWidget_C'"));

	if (Lobby.Succeeded())
	{
		LobbyWidgetClass = Lobby.Class;
	}
}

void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);

	if (LobbyWidgetClass)
	{
		LobbyWidget = CreateWidget<ULobbyWidget>(GetWorld(), LobbyWidgetClass);
		LobbyWidget->AddToViewport();
	}
}
