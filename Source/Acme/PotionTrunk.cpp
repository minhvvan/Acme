// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionTrunk.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "AcmeCharacter.h"
#include "Acme/Widget/PotionCraftWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Acme/Utils/Util.h"

APotionTrunk::APotionTrunk()
{
	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(RootComponent);
	OverlapComp->InitSphereRadius(300.f);

	Indicator = CreateDefaultSubobject<UWidgetComponent>(TEXT("Indicator"));
	Indicator->SetupAttachment(RootComponent);
}

void APotionTrunk::Interact()
{
	if (!OverlappedCharacter) return;
	if (!WidgetClass) return;

	auto PC = Cast<APlayerController>(OverlappedCharacter->GetController());
	if (!PC) return;

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;

	InteractWidget = CreateWidget<UPotionCraftWidget>(GetWorld(), WidgetClass);
	if (!InteractWidget) return;

	if (InteractSFX) UGameplayStatics::SpawnSoundAtLocation(GetWorld(), InteractSFX, GetActorLocation());

	InteractWidget->AddToViewport();
}

void APotionTrunk::BeginPlay()
{
	Super::BeginPlay();

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &APotionTrunk::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &APotionTrunk::OnEndOverlap);

	SetVisibleIndicator(false);
}

void APotionTrunk::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlappedCharacter) return;
		Mesh->SetRenderCustomDepth(true);
		SetVisibleIndicator(true);
	}
}

void APotionTrunk::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = nullptr;
		Mesh->SetRenderCustomDepth(false);
		SetVisibleIndicator(false);
	}
}

void APotionTrunk::SetVisibleIndicator(bool bVisible)
{
	if (!IsValid(Indicator)) return;
	Indicator->SetVisibility(bVisible);
}