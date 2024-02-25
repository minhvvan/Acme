// Fill out your copyright notice in the Description page of Project Settings.


#include "CookPot.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "AcmeCharacter.h"
#include "Acme/Widget/CookPotWidget.h"


ACookPot::ACookPot()
{
	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(RootComponent);
	OverlapComp->InitSphereRadius(100.f);

	Indicator = CreateDefaultSubobject<UWidgetComponent>(TEXT("Indicator"));
	Indicator->SetupAttachment(RootComponent);
}

void ACookPot::BeginPlay()
{
	Super::BeginPlay();

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ACookPot::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &ACookPot::OnEndOverlap);

	SetVisibleIndicator(false);
}

void ACookPot::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = Cast<AAcmeCharacter>(OtherActor);
		SetVisibleIndicator(true);
	}
}

void ACookPot::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = nullptr;
		SetVisibleIndicator(false);
	}
}

void ACookPot::SetVisibleIndicator(bool bVisible)
{
	if (!IsValid(Indicator)) return;
	Indicator->SetVisibility(bVisible);
}

void ACookPot::Interact()
{
	if (!OverlappedCharacter) return;
	if (!WidgetClass) return;

	auto PC = Cast<APlayerController>(OverlappedCharacter->GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;

	InteractWidget = CreateWidget<UCookPotWidget>(GetWorld(), WidgetClass);
	if (!InteractWidget) return;

	InteractWidget->AddToViewport();
}
