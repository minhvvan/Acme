// Fill out your copyright notice in the Description page of Project Settings.


#include "AcmePC.h"
#include "Acme/Utils/Util.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Framework/AcmeSaveGame.h"

void AAcmePC::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
}

void AAcmePC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	UAcmeSaveGame* SaveGame = GameInstance->GetCurrentSaveGame();

	AAcmeCharacter* CurrentPawn = Cast<AAcmeCharacter>(GetPawn());
	if (CurrentPawn && SaveGame)
	{
		CurrentPawn->SetActorLocation(SaveGame->CurrentPos);
		CurrentPawn->SetCurrentHP(SaveGame->CurrentHP);
		CurrentPawn->SetCurrentSatiety(SaveGame->CurrentSatiety);
		CurrentPawn->SetInventory(SaveGame->Inventory);
		CurrentPawn->SetQuickSlots(SaveGame->QuickSlot);

		CurrentPawn->Equip(EEquipmentPart::E_Head, SaveGame->EquipmentHead);
		CurrentPawn->Equip(EEquipmentPart::E_Body, SaveGame->EquipmentBody);
		CurrentPawn->Equip(EEquipmentPart::E_Accessory, SaveGame->EquipmentAcc);
	}
}
