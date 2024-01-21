// Fill out your copyright notice in the Description page of Project Settings.


#include "AlchemicCauldron.h"
#include "Acme/Utils/Util.h"
#include "Acme/Widget/AlchemicComposeWidget.h"
#include "AcmeCharacter.h"

AAlchemicCauldron::AAlchemicCauldron()
{
}

void AAlchemicCauldron::BeginPlay()
{
	Super::BeginPlay();
	SetbCanOverlap(true);

	if (WidgetClass)
	{
		InteractWidget = Cast<UAlchemicComposeWidget>(CreateWidget(GetWorld(), WidgetClass));
	}
}

void AAlchemicCauldron::Interact()
{
	if (!InteractWidget) return;
	if (!OverlapedCharacter) return;

	OverlapedCharacter->SetIsOpenWidget(true);
	OverlapedCharacter->SetInteractWidget(InteractWidget);

	auto PC = Cast<APlayerController>(OverlapedCharacter->GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->SetPause(true);
	PC->bShowMouseCursor = true;

	InteractWidget->AddToViewport();
}
