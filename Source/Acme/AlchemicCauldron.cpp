// Fill out your copyright notice in the Description page of Project Settings.


#include "AlchemicCauldron.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "AcmeCharacter.h"
#include "Acme/Utils/Util.h"
#include "Acme/Widget/AlchemicComposeWidget.h"
#include "Acme/Data/ElementData.h"

AAlchemicCauldron::AAlchemicCauldron()
{
	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(RootComponent);
	OverlapComp->InitSphereRadius(100.f);

	Indicator = CreateDefaultSubobject<UWidgetComponent>(TEXT("Indicator"));
	Indicator->SetupAttachment(RootComponent);
}

void AAlchemicCauldron::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		InteractWidget = Cast<UAlchemicComposeWidget>(CreateWidget(GetWorld(), WidgetClass));
	}

	SetVisibleIndicator(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AAlchemicCauldron::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &AAlchemicCauldron::OnEndOverlap);
}

void AAlchemicCauldron::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = Cast<AAcmeCharacter>(OtherActor);
		SetVisibleIndicator(true);
	}
}

void AAlchemicCauldron::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		if (Cast<AAcmeCharacter>(OtherActor))
		{
			OverlappedCharacter = nullptr;
			SetVisibleIndicator(false);
		}
	}
}

void AAlchemicCauldron::SetVisibleIndicator(bool bVisible)
{
	if (!IsValid(Indicator)) return;

	Indicator->SetVisibility(bVisible);
}

void AAlchemicCauldron::Interact()
{
	if (!InteractWidget) return;
	if (!OverlappedCharacter) return;

	OverlappedCharacter->SetIsOpenWidget(true);
	OverlappedCharacter->SetInteractWidget(InteractWidget);

	auto PC = Cast<APlayerController>(OverlappedCharacter->GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	//PC->SetPause(true);
	PC->bShowMouseCursor = true;

	InteractWidget->AddToViewport();
}
