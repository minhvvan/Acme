// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Lobby/LobbyGameMode.h"
#include "Acme/Lobby/LobbyPC.h"

ALobbyGameMode::ALobbyGameMode()
{
	PlayerControllerClass = ALobbyPC::StaticClass();
}
