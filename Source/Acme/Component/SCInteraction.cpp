// Fill out your copyright notice in the Description page of Project Settings.


#include "SCInteraction.h"
#include "Components/SphereComponent.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"
#include "Acme/ActorInteractive.h"

// Sets default values for this component's properties
USCInteraction::USCInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

}


// Called when the game starts
void USCInteraction::BeginPlay()
{
	Super::BeginPlay();
}

void USCInteraction::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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

