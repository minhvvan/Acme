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
			//TODO: ���� ����, ���ڸ��� ���ư���
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
	//������ ���� -> Damage + �з�����

	UUtil::DebugPrint("Evaporation");
}

void ACharacterMonster::Combustion()
{
	//fire + Air
	//���� -> ȭ�� -> �̹� ȭ���̸� 2��(�ð��� ����)
}

void ACharacterMonster::Melting()
{
	//fire + Ice = Water
	//���� -> ������ ���� -> Damage or Groggy

}

void ACharacterMonster::Spread()
{
	//fire + Thunder = Thunder�� �ֺ����� ����

}

void ACharacterMonster::Frozen()
{
	//Water + Ice = ���ӵ� ������ ��� �������� ����

}

void ACharacterMonster::Stunned()
{
	//Water + Thunder = ������ ����(CC)
	OnElectricShock();
}


void ACharacterMonster::Weathered()
{
	//earth + Air
	//ǳȭ -> ���� ����
}

void ACharacterMonster::Swamp()
{
	//water + earth
	//���� -> Slow
}

void ACharacterMonster::OnFrozen()
{
	//frozen�Ǹ� ó�� ���� -> �ִ�ü�� n%
}

void ACharacterMonster::OnElectricShock()
{
	//�������¿��� ������ ����
}
