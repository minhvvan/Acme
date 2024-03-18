// Fill out your copyright notice in the Description page of Project Settings.


#include "AcmePC.h"
#include "Acme/Utils/Util.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/Framework/AcmeSaveGame.h"
#include "Acme/Widget/GuideWidget.h"

AAcmePC::AAcmePC()
{
	ConstructorHelpers::FClassFinder<UGuideWidget> GUIDE(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Acme/Widgets/WBP_Guide.WBP_Guide_C'"));
	if (GUIDE.Succeeded())
	{
		GuideClass = GUIDE.Class;
	}
}

void AAcmePC::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();

	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	UAcmeSaveGame* SaveGame = GameInstance->GetCurrentSaveGame();
	if (!SaveGame)
	{
		GuideWidget = CreateWidget<UGuideWidget>(GetWorld(), GuideClass);
		GuideWidget->AddToViewport(1);

		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
		return;
	}

	if (SaveGame->bOpenGuide)
	{
		GuideWidget = CreateWidget<UGuideWidget>(GetWorld(), GuideClass);
		GuideWidget->AddToViewport(1);

		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

void AAcmePC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (!GameInstance) GameInstance = GetGameInstance<UAcmeGameInstance>();

	UAcmeSaveGame* SaveGame = GameInstance->GetCurrentSaveGame();
	AAcmeCharacter* CurrentPawn = Cast<AAcmeCharacter>(GetPawn());

	if (!CurrentPawn || !SaveGame) return;

	CurrentPawn->SetActorLocation(SaveGame->CurrentPos);
	CurrentPawn->SetCurrentHP(SaveGame->CurrentHP);
	CurrentPawn->SetCurrentSatiety(SaveGame->CurrentSatiety);
	CurrentPawn->SetInventory(SaveGame->Inventory);
	CurrentPawn->SetQuickSlots(SaveGame->QuickSlot);

	CurrentPawn->Equip(EEquipmentPart::E_Head, SaveGame->EquipmentHead);
	CurrentPawn->Equip(EEquipmentPart::E_Body, SaveGame->EquipmentBody);
	CurrentPawn->Equip(EEquipmentPart::E_Accessory, SaveGame->EquipmentAcc);
}