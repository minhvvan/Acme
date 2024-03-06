// Fill out your copyright notice in the Description page of Project Settings.


#include "FireArea.h"
#include "Components/BoxComponent.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"


// Sets default values
AFireArea::AFireArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	SetRootComponent(Area);

	LifeTime = 10.f;
}

// Called when the game starts or when spawned
void AFireArea::BeginPlay()
{
	Super::BeginPlay();
	
	Area->OnComponentBeginOverlap.AddDynamic(this, &AFireArea::OnBeginOverlap);

	//º“∏Í ≈∏¿Ã∏”
	GetWorldTimerManager().SetTimer(LifeTimer, FTimerDelegate::CreateLambda([this]() {
		Destroy();
		}), LifeTime, false);
}

void AFireArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor != GetInstigator())
	{
		AAcmeCharacter* Player = Cast<AAcmeCharacter>(OtherActor);
		if (!Player) return;

		Player->Burn();
	}
}

// Called every frame
void AFireArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

