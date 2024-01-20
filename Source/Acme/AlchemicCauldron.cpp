// Fill out your copyright notice in the Description page of Project Settings.


#include "AlchemicCauldron.h"
#include "Acme/Utils/Util.h"
#include "Acme/Widget/AlchemicComposeWidget.h"

AAlchemicCauldron::AAlchemicCauldron()
{

}

void AAlchemicCauldron::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		InteractWidget = Cast<UAlchemicComposeWidget>(CreateWidget(GetWorld(), WidgetClass));
	}
}

void AAlchemicCauldron::Interact()
{
	UUtil::DebugPrint("Inter");
	if (!InteractWidget) return;

	InteractWidget->AddToViewport();
}
