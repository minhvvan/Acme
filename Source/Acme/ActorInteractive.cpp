// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorInteractive.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "AcmeCharacter.h"
#include "Acme/Widget/WidgetIndicator.h"
#include "Acme/Utils/Util.h"


// Sets default values
AActorInteractive::AActorInteractive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Indicator = CreateDefaultSubobject<UWidgetComponent>(TEXT("Indicator"));
	Indicator->SetupAttachment(RootComponent);
	
	Name = EItemName::E_Empty;

	bCanInteract = false;
	bCanOverlap = false;
}

// Called when the game starts or when spawned
void AActorInteractive::BeginPlay()
{
	Super::BeginPlay();

	if (UWidgetIndicator* IndicatorWidget = Cast<UWidgetIndicator>(Indicator->GetWidget()))
	{
		IndicatorWidget->SetName(NameStrings[Name]);
	}
}

void AActorInteractive::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr && bCanOverlap)
	{
		OverlapedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlapedCharacter) return;

		bCanInteract = true;
		bCanOverlap = false;

		SetVisibleIndicator(true);
	}
}

void AActorInteractive::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlapedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlapedCharacter) return;

		bCanInteract = false;
		bCanOverlap = true;

		SetVisibleIndicator(false);
	}
}

// Called every frame
void AActorInteractive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorInteractive::SetVisibleIndicator(bool bVisible)
{
	//indicator visible set
	if (!IsValid(Indicator)) return;

	Indicator->SetVisibility(bVisible);
}

void AActorInteractive::Interact()
{
	//OverlapedCharacter->Do Something
}

bool AActorInteractive::GetbCanInteract()
{
	return bCanInteract;
}

void AActorInteractive::SetbCanInteract(bool canInteract)
{
	bCanInteract = canInteract;
}