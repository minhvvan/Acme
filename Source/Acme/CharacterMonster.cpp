// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMonster.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AC_Stat.h"
#include "Widget_HPBar.h"


// Sets default values
ACharacterMonster::ACharacterMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatCompoenent = CreateDefaultSubobject<UAC_Stat>(TEXT("Stat"));

	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACharacterMonster::BeginPlay()
{
	Super::BeginPlay();
	
	InitState();

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

void ACharacterMonster::OnAttacked(int damage)
{
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

void ACharacterMonster::InitState()
{
	auto HpBar = Cast<UWidget_HPBar>(HPBar->GetWidget());
	HpBar->BindDelegate(StatCompoenent);
	HpBar->SetHPPercent(100, 100);
}

void ACharacterMonster::Die()
{
	//Play Die Montage -> ³¡³ª¸é Destroy()
	Destroy();

	OnDied.Broadcast();
}

