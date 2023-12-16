// Fill out your copyright notice in the Description page of Project Settings.


#include "SCInteraction.h"
#include "Components/SphereComponent.h"
#include "AcmeCharacter.h"
#include "Util.h"
#include "ActorInteractive.h"

// Sets default values for this component's properties
USCInteraction::USCInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("SphereOverlap"));
	SphereOverlap->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
}


// Called when the game starts
void USCInteraction::BeginPlay()
{
	Super::BeginPlay();

	SphereOverlap->OnComponentBeginOverlap.AddDynamic(this, &USCInteraction::OnBeginOverlap);
	SphereOverlap->OnComponentEndOverlap.AddDynamic(this, &USCInteraction::OnEndOverlap);
	
	SphereOverlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void USCInteraction::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UUtil::DebugPrint("OVerlap");

	if (OtherActor != nullptr && OtherActor != this->GetOwner() && OtherComp != nullptr)
	{
		AAcmeCharacter* Character = Cast<AAcmeCharacter>(OtherActor);
		if (!Character) return;

		Character->SetOverlapActor(Cast<AActorInteractive>(this->GetOwner()));
	}
}

void USCInteraction::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void USCInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

