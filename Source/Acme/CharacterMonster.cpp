// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMonster.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MonsterStatComponent.h"
#include "Widget_HPBar.h"
#include "AI_Monster.h"
#include "Util.h"


// Sets default values
ACharacterMonster::ACharacterMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatCompoenent = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("Stat"));

	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->SetupAttachment(RootComponent);

	IsCombat = false;
	CombatSustainTime = 5.f;
}

// Called when the game starts or when spawned
void ACharacterMonster::BeginPlay()
{
	Super::BeginPlay();
	
	InitState();

	AnimInstance = Cast<UAI_Monster>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &ACharacterMonster::OnMontageEnd);
}

// Called every frame
void ACharacterMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterMonster::OnAttacked(int damage, EElement ElementType)
{
	IsCombat = true;
	HPBar->SetVisibility(true);

	if (ElementType != EElement::E_Normal)
	{
		Cast<UWidget_HPBar>(HPBar->GetWidget())->AddElement(ElementType);
		ElementReaction(ElementType);
	}

	GetWorldTimerManager().SetTimer(CombatTimer, FTimerDelegate::CreateLambda(
		[this]() {
			IsCombat = false;
			HPBar->SetVisibility(false);
			//TODO: 전투 종료, 제자리로 돌아가게
		}), CombatSustainTime, false);

	int CurrentHP = StatCompoenent->GetCurrentHP();
	int newHP = CurrentHP - damage;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("newHP: %d"), newHP));

	if (newHP < 0)
	{
		newHP = 0;
	}

	StatCompoenent->SetCurrentHP(newHP);

	if (newHP == 0) Die();
}

void ACharacterMonster::Attack()
{
	IsCombat = true;
	HPBar->SetVisibility(true);

}

void ACharacterMonster::InitState()
{
	auto HpBar = Cast<UWidget_HPBar>(HPBar->GetWidget());
	HpBar->BindDelegate(StatCompoenent);
	HpBar->SetHPPercent(100, 100);

	HPBar->SetVisibility(false);

	ElementReactions[(int)EElement::E_Fire][(int)EElement::E_Water] = &ACharacterMonster::Evaporation;
	ElementReactions[(int)EElement::E_Fire][(int)EElement::E_Air] = &ACharacterMonster::Combustion;
	ElementReactions[(int)EElement::E_Fire][(int)EElement::E_Ice] = &ACharacterMonster::Melting;
	ElementReactions[(int)EElement::E_Fire][(int)EElement::E_Thunder] = &ACharacterMonster::Spread;	
	
	ElementReactions[(int)EElement::E_Water][(int)EElement::E_Fire] = &ACharacterMonster::Evaporation;
	ElementReactions[(int)EElement::E_Air][(int)EElement::E_Fire] = &ACharacterMonster::Combustion;
	ElementReactions[(int)EElement::E_Ice][(int)EElement::E_Fire] = &ACharacterMonster::Melting;
	ElementReactions[(int)EElement::E_Thunder][(int)EElement::E_Fire] = &ACharacterMonster::Spread;


	ElementReactions[(int)EElement::E_Water][(int)EElement::E_Ice] = &ACharacterMonster::Frozen;
	ElementReactions[(int)EElement::E_Water][(int)EElement::E_Thunder] = &ACharacterMonster::Stunned;	
	
	ElementReactions[(int)EElement::E_Ice][(int)EElement::E_Water] = &ACharacterMonster::Frozen;
	ElementReactions[(int)EElement::E_Thunder][(int)EElement::E_Water] = &ACharacterMonster::Stunned;
	

	ElementReactions[(int)EElement::E_Earth][(int)EElement::E_Air] = &ACharacterMonster::Weathered;
	ElementReactions[(int)EElement::E_Earth][(int)EElement::E_Water] = &ACharacterMonster::Swamp;

	ElementReactions[(int)EElement::E_Air][(int)EElement::E_Earth] = &ACharacterMonster::Weathered;
	ElementReactions[(int)EElement::E_Water][(int)EElement::E_Earth] = &ACharacterMonster::Swamp;


	ElementReactions[(int)EElement::E_Ice][(int)EElement::E_Ice] = &ACharacterMonster::OnFrozen;
}

void ACharacterMonster::Die()
{
	AnimInstance->PlayDeath();
}

void ACharacterMonster::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	Destroy();
	OnDied.Broadcast();
}

void ACharacterMonster::ElementReaction(EElement element)
{
	if (Elements.IsEmpty())
	{
		Elements.Push(element);
		return;
	}

	Elements.Push(element);

	//Reaction
	while (FlushElements())
	{
		//TODO: UI Update
	}
}

bool ACharacterMonster::FlushElements()
{
	int Second = (int)Elements.Last();
	Elements.Pop();

	int First = (int)Elements.Last();
	Elements.Pop();

	if (ElementReactions[First][Second] == nullptr)
	{
		Elements.Push(static_cast<EElement>(First));
		Elements.Push(static_cast<EElement>(Second));

		return false;
	}

	(this->* (ElementReactions[First][Second]))();

	if (Elements.Num() < 2) return false;
	return true;
}

void ACharacterMonster::Evaporation()
{
	//fire + water = Air
	//수증기 폭발 -> Damage + 밀려나게

	UUtil::DebugPrint("Evaporation");
}

void ACharacterMonster::Combustion()
{
	//fire + Air
	//연소 -> 화상 -> 이미 화상이면 2배(시간은 리셋)
}

void ACharacterMonster::Melting()
{
	//fire + Ice = Water
	//융해 -> 에너지 뺏김 -> Damage or Groggy

}

void ACharacterMonster::Spread()
{
	//fire + Thunder = Thunder가 주변으로 퍼짐

}

void ACharacterMonster::Frozen()
{
	//Water + Ice = 연속된 물원소 모두 얼음으로 변경

}

void ACharacterMonster::Stunned()
{
	//Water + Thunder = 무조건 스턴(CC)
	OnElectricShock();
}


void ACharacterMonster::Weathered()
{
	//earth + Air
	//풍화 -> 방어력 감소
}

void ACharacterMonster::Swamp()
{
	//water + earth
	//습지 -> Slow
}

void ACharacterMonster::OnFrozen()
{
	//frozen되면 처형 가능 -> 최대체력 n%
}

void ACharacterMonster::OnElectricShock()
{
	//감전상태에서 붙으면 감전
}
