// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorInteractive.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "AcmeCharacter.h"
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
}

// Called when the game starts or when spawned
void AActorInteractive::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AActorInteractive::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &AActorInteractive::OnEndOverlap);
}

void AActorInteractive::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UUtil::DebugPrint("OVerlap");

	if (OtherActor != nullptr && OtherActor != this->GetOwner() && OtherComp != nullptr)
	{
		AAcmeCharacter* Character = Cast<AAcmeCharacter>(OtherActor);
		if (!Character) return;

		Character->SetOverlapActor(this);
	}
}

void AActorInteractive::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor != this->GetOwner() && OtherComp != nullptr)
	{
		AAcmeCharacter* Character = Cast<AAcmeCharacter>(OtherActor);
		if (!Character) return;

		Character->SetOverlapActor(nullptr);
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
	UUtil::DebugPrint("SetVisibleIndicator");
	if (!IsValid(Indicator)) return;

	Indicator->SetVisibility(bVisible);
}