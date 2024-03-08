// Copyright Epic Games, Inc. All Rights Reserved.

#include "AcmeGameMode.h"
#include "AcmeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAcmeGameMode::AAcmeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Acme/BluePrint/BP_Character.BP_Character_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}
