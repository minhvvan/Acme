// Fill out your copyright notice in the Description page of Project Settings.


#include "Worktable.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "AcmeCharacter.h"
#include "Acme/Widget/WorktableWidget.h"


AWorktable::AWorktable()
{
	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(RootComponent);
	OverlapComp->InitSphereRadius(100.f);

	Indicator = CreateDefaultSubobject<UWidgetComponent>(TEXT("Indicator"));
	Indicator->SetupAttachment(RootComponent);
}

void AWorktable::BeginPlay()
{
	Super::BeginPlay();

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AWorktable::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &AWorktable::OnEndOverlap);

	SetVisibleIndicator(false);
}

void AWorktable::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = Cast<AAcmeCharacter>(OtherActor);
		SetVisibleIndicator(true);
	}
}

void AWorktable::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = nullptr;
		SetVisibleIndicator(true);
	}
}

void AWorktable::SetVisibleIndicator(bool bVisible)
{
	if (!IsValid(Indicator)) return;
	Indicator->SetVisibility(bVisible);
}

void AWorktable::Interact()
{
	if (!OverlappedCharacter) return;

	auto PC = Cast<APlayerController>(OverlappedCharacter->GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;

	InteractWidget = CreateWidget<UWorktableWidget>(GetWorld(), WidgetClass);
	if (!InteractWidget) return;

	InteractWidget->AddToViewport();
}
