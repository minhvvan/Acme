// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_Monster.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "AC_Stat.h"
#include "Widget_HPBar.h"

// Sets default values
APawn_Monster::APawn_Monster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->bOwnerNoSee = false;
	Mesh->SetupAttachment(CapsuleComponent);

	static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
	Mesh->SetCollisionProfileName(MeshCollisionProfileName);
	Mesh->SetGenerateOverlapEvents(false);

	StatCompoenent = CreateDefaultSubobject<UAC_Stat>(TEXT("Stat"));

	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APawn_Monster::BeginPlay()
{
	Super::BeginPlay();
	
	InitState();
}

// Called every frame
void APawn_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawn_Monster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawn_Monster::OnAttacked(int damage)
{
	if (!StatCompoenent) return;

	int CurrentHP = StatCompoenent->GetCurrentHP();
	int newHP = CurrentHP - damage;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("newHP: %d"), newHP));

	if (newHP < 0)
	{
		newHP = 0;
	}

	StatCompoenent->SetCurrentHP(newHP);

	if (newHP == 0) Die();
}

void APawn_Monster::InitState()
{
	//Stat 초기화

	auto HpBar = Cast<UWidget_HPBar>(HPBar->GetWidget());
	HpBar->BindDelegate(StatCompoenent);
	HpBar->SetHPPercent(100, 100);
}

void APawn_Monster::Die()
{
	//Play Die Montage -> 끝나면 Destroy()
	Destroy();
}

