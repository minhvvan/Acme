#include "AC_Stat.h"
#include "Util.h"

UAC_Stat::UAC_Stat()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHP = 100;
	MaxHP = 100;

	CurrentSatiety = 100;

	Strength = 10;
	Dexterity = 10;
	Intelligence = 10;

	CoolTimedash = 2.f;
	ConsumeTimeSatiety = 30.f;
	ConsumeAmountSatiety = 1;
}


// Called when the game starts
void UAC_Stat::BeginPlay()
{
	Super::BeginPlay();

	//TODO: load data

	//¹è°íÇÄ ¼Òºñ
	float time = ConsumeTimeSatiety;

	GetWorld()->GetTimerManager().SetTimer(TimerSatiety, 
		FTimerDelegate::CreateLambda([this, time]() {
			SetCurrentST(GetCurrentST() - ConsumeAmountSatiety);
		}),
		time, true);
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

void UAC_Stat::SetCurrentHP(int HP)
{
	CurrentHP = HP;

	OnChangedHP.Broadcast(CurrentHP, MaxHP);
}

void UAC_Stat::SetCurrentST(int ST)
{
	CurrentSatiety = ST;

	OnChangedST.Broadcast(CurrentSatiety);
}

void UAC_Stat::OnAttakced(int damage)
{
	int newHP = CurrentHP - damage;
	if (newHP < 0) newHP = 0;
	SetCurrentHP(newHP);
}

void UAC_Stat::OnConsumeSatiety(int amount)
{
	int newSatiety = CurrentSatiety - amount;
	if (newSatiety < 0) newSatiety = 0;
	SetCurrentST(newSatiety);
}
