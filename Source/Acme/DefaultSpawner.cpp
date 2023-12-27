// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Util.h"

// Sets default values
ADefaultSpawner::ADefaultSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));

	SetRootComponent(Area);

	MaxPopulation = 10;
	RespawnInterval = 30.f;
}

// Called when the game starts or when spawned
void ADefaultSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

