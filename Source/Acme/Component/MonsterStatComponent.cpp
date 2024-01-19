// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStatComponent.h"

// Sets default values for this component's properties
UMonsterStatComponent::UMonsterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHP = 100;
	MaxHP = 100;

	Strength = 10;
}


// Called when the game starts
void UMonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMonsterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UMonsterStatComponent::GetCurrentHP()
{
	return CurrentHP;
}

void UMonsterStatComponent::SetCurrentHP(int HP)
{
	CurrentHP = HP;
	OnChangedHP.Broadcast(CurrentHP, MaxHP);
}

int UMonsterStatComponent::GetStrength()
{
	return Strength;
}

