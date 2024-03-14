// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/CraftTable.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "AcmeCharacter.h"
#include "Acme/Widget/CraftTableWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Acme/Utils/Util.h"

ACraftTable::ACraftTable()
{
	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(RootComponent);
	OverlapComp->InitSphereRadius(300.f);

	Indicator = CreateDefaultSubobject<UWidgetComponent>(TEXT("Indicator"));
	Indicator->SetupAttachment(RootComponent);
}

void ACraftTable::Interact()
{
	if (!OverlappedCharacter) return;
	if (!WidgetClass) return;

	auto PC = Cast<APlayerController>(OverlappedCharacter->GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;

	InteractWidget = CreateWidget<UCraftTableWidget>(GetWorld(), WidgetClass);
	if (!InteractWidget) return;

	if (InteractSFX) UGameplayStatics::SpawnSoundAtLocation(GetWorld(), InteractSFX, GetActorLocation());

	InteractWidget->AddToViewport();
}

void ACraftTable::BeginPlay()
{
	Super::BeginPlay();

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ACraftTable::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &ACraftTable::OnEndOverlap);

	SetVisibleIndicator(false);
}

void ACraftTable::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlappedCharacter) return;
		Mesh->SetRenderCustomDepth(true);
		SetVisibleIndicator(true);
	}
}

void ACraftTable::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = nullptr;
		Mesh->SetRenderCustomDepth(false);
		SetVisibleIndicator(false);
	}
}

void ACraftTable::SetVisibleIndicator(bool bVisible)
{
	if (!IsValid(Indicator)) return;
	Indicator->SetVisibility(bVisible);
}
