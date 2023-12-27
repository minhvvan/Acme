// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorInteractive.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "AcmeCharacter.h"
#include "WidgetIndicator.h"
#include "Util.h"


// Sets default values
AActorInteractive::AActorInteractive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(RootComponent);
	OverlapComp->InitSphereRadius(100.f);

	Indicator = CreateDefaultSubobject<UWidgetComponent>(TEXT("Indicator"));
	Indicator->SetupAttachment(RootComponent);

	Name = TEXT("Name");
}

// Called when the game starts or when spawned
void AActorInteractive::BeginPlay()
{
	Super::BeginPlay();

	if (UWidgetIndicator* IndicatorWidget = Cast<UWidgetIndicator>(Indicator->GetWidget()))
	{
		IndicatorWidget->SetName(Name);
	}
	
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AActorInteractive::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &AActorInteractive::OnEndOverlap);
}

void AActorInteractive::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this->GetOwner() && OtherComp != nullptr)
	{
		OverlapedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlapedCharacter) return;

		OverlapedCharacter->SetOverlapActor(this);
	}
}

void AActorInteractive::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor != this->GetOwner() && OtherComp != nullptr)
	{
		OverlapedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlapedCharacter) return;

		OverlapedCharacter->SetOverlapActor(nullptr);
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
	Destroy();
}

void AActorInteractive::SetName(FString newName)
{
	Name = newName;
	if (UWidgetIndicator* IndicatorWidget = Cast<UWidgetIndicator>(Indicator->GetWidget()))
	{
		IndicatorWidget->SetName(newName);
	}
}
