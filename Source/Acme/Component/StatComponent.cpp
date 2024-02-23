// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "Acme/Utils/Util.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHP = 100;
	MaxHP = 100;

	CurrentStamina = 100;
	MaxStamina = 100;

	CurrentSatiety = 100;

	Strength = 10;
	Dexterity = 10;
	Intelligence = 10;

	CoolTimedash = 2.f;
	ConsumeTimeSatiety = 30.f;
	ConsumeAmountSatiety = 1;

	RecoveryTime = 3.f;
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	//¹è°íÇÄ ¼Òºñ
	GetWorld()->GetTimerManager().SetTimer(TimerSatiety,
		FTimerDelegate::CreateLambda([this]() {
			SetCurrentST(GetCurrentST() - ConsumeAmountSatiety);
			}),
		ConsumeTimeSatiety, true);
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatComponent::SetCurrentHP(int HP)
{
	CurrentHP = HP;
	OnChangedHP.Broadcast(CurrentHP, MaxHP);
}

void UStatComponent::SetCurrentST(int ST)
{
	CurrentSatiety = ST;
	OnChangedST.Broadcast(CurrentSatiety);
}

void UStatComponent::SetCurrentStamina(int Stamina)
{
	CurrentStamina = Stamina;
	OnChangedStamina.Broadcast(CurrentStamina);
}

void UStatComponent::OnAttakced(int damage)
{
	int newHP = CurrentHP - damage;
	if (newHP < 0) newHP = 0;
	SetCurrentHP(newHP);
}

void UStatComponent::OnConsumeSatiety(int amount)
{
	int newSatiety = CurrentSatiety - amount;
	if (newSatiety <= 0) newSatiety = 0;
	SetCurrentST(newSatiety);
}

void UStatComponent::ConsumeStamina(int amount)
{
	int newCurrentStamina = CurrentStamina - amount;
	if (newCurrentStamina < 0) newCurrentStamina = 0;

	SetCurrentStamina(newCurrentStamina);

	GetWorld()->GetTimerManager().ClearTimer(StaminaRecoveryTimer);
	GetWorld()->GetTimerManager().SetTimer(StaminaRecoveryTimer,
		FTimerDelegate::CreateLambda([this]() {
			RecoveryStamina(100);
			}),
		RecoveryTime, true);
}

void UStatComponent::RecoveryStamina(int amount)
{
	int newCurrentStamina = CurrentStamina + amount;
	if (newCurrentStamina > 100) newCurrentStamina = 100;

	SetCurrentStamina(newCurrentStamina);
}

void UStatComponent::StartSprint()
{
	GetWorld()->GetTimerManager().SetTimer(TimerSprint, FTimerDelegate::CreateLambda(
		[this]()->void
		{
			ConsumeStamina(5);
		}
	), .5f, true);
}

void UStatComponent::EndSprint()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerSprint);
}

void UStatComponent::AddSatiety(int amount)
{
	int newSatiety = CurrentSatiety + amount;
	if (newSatiety > 100) newSatiety = 100;


	SetCurrentST(newSatiety);
}