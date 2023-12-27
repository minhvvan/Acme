#include "AC_Stat.h"
#include "Util.h"

UAC_Stat::UAC_Stat()
{
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
}


// Called when the game starts
void UAC_Stat::BeginPlay()
{
	Super::BeginPlay();

	//TODO: load data

	//¹è°íÇÄ ¼Òºñ
	GetWorld()->GetTimerManager().SetTimer(TimerSatiety, 
		FTimerDelegate::CreateLambda([this]() {
			SetCurrentST(GetCurrentST() - ConsumeAmountSatiety);
		}),
		ConsumeTimeSatiety, true);

}


// Called every frame
void UAC_Stat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

void UAC_Stat::SetCurrentStamina(int Stamina)
{
	CurrentStamina = Stamina;
	OnChangedStamina.Broadcast(CurrentStamina);
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
	if (newSatiety <= 0) newSatiety = 0;
	SetCurrentST(newSatiety);
}

void UAC_Stat::ComsumeStamina(int amount)
{
	int newCurrentStamina = CurrentStamina - amount;
	if (newCurrentStamina < 0) newCurrentStamina = 0;

	SetCurrentStamina(newCurrentStamina);
}

void UAC_Stat::RecoveryStamina(int amount)
{
	int newCurrentStamina = CurrentStamina + amount;
	if (newCurrentStamina > 100) newCurrentStamina = 100;

	SetCurrentStamina(newCurrentStamina);
}

void UAC_Stat::AddElement(EElement element)
{
	if (Elements.Contains(element))
	{
		Elements[element]++;
	}
	else
	{
		Elements.Add({ element, 1 });
	}


	for (auto e : Elements)
	{
		switch (e.Key)
		{
		case EElement::E_Fire:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Fire: %d"), e.Value));
			break;
		case EElement::E_Water:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Water: %d"), e.Value));
			break;
		case EElement::E_Earth:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Earth: %d"), e.Value));
			break;
		case EElement::E_Air:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Air: %d"), e.Value));
			break;
		case EElement::E_Ice:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Ice: %d"), e.Value));
			break;
		case EElement::E_Thunder:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Thunder: %d"), e.Value));
			break;
		case EElement::E_Normal:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Normal: %d"), e.Value));
			break;
		}
	}
}
