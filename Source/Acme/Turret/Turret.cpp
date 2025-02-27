// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Turret/Turret.h"
#include "Acme/Utils/Util.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/AcmeCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->SetupAttachment(RootComponent);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DestroyTimer, FTimerDelegate::CreateLambda(
		[this]() { Destroy(); }
	), Time, false);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATurret::PlayFireSFX()
{
	if (FireSFX)
	{
		AudioComp->SetSound(FireSFX);

		if (AudioComp->IsPlaying()) AudioComp->Stop();
		AudioComp->Play();
	}
}

void ATurret::PlayFindEnermySFX()
{
	if (FireSFX)
	{
		AudioComp->SetSound(FindEmermySFX);

		if (AudioComp->IsPlaying()) AudioComp->Stop();
		AudioComp->Play();
	}
}

void ATurret::PlayFireFX(bool bOnTarget)
{
	if(bOnTarget) Niagara->SetActive(bOnTarget);
	else Niagara->Deactivate();
}

void ATurret::Fire()
{
	if (!Target) return;
	AAcmeCharacter* Player = GetInstigator<AAcmeCharacter>();
	if (!Player) return;

	FVector CenterPos = GetActorLocation();
	FRotator Rot = (Target->GetActorLocation() - CenterPos).Rotation();
	Rot.Pitch = 0;
	Rot.Roll = 0;

	FQuat quat = Rot.Quaternion();
	SetActorRotation(quat);

	Target->SetTarget(Player);
	Target->OnAttacked(Damage);

	PlayFireFX(true);
	PlayFireSFX();
}

void ATurret::SetTarget(ACharacterMonster* newTarget)
{
	if (newTarget == nullptr) PlayFireFX(false);
	Target = newTarget;
}