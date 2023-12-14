#include "AC_Stat.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_Stat.h"
#include "Util.h"

// Sets default values for this component's properties
UAC_Stat::UAC_Stat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_Stat::BeginPlay()
{
	Super::BeginPlay();

	//TODO: load data

	CurrentHP = 100;
	CurrentHP = 100;

	Strength = 10;
	Dexterity = 10;
	Intelligence = 10;

	CoolTimedash = 2.f;
}


// Called every frame
void UAC_Stat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_Stat::ExeDash()
{
	float time = CoolTimedash - (Dexterity * .01);

	if (time <= 0)
	{
		CDDash.Broadcast();
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(
		TimerDash,
		FTimerDelegate::CreateLambda([this, time]() {
				CDDash.Broadcast();
			}), 
		time, false);
}