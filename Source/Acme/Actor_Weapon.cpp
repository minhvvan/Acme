// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Weapon.h"
#include "AcmeCharacter.h"
#include "Components/AudioComponent.h"

// Sets default values
AActor_Weapon::AActor_Weapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));

	CurrentType = EElement::E_Normal;

	WeaponTopName = FName(TEXT("WeaponTop"));
	WeaponEndName = FName(TEXT("WeaponEnd"));
}

// Called when the game starts or when spawned
void AActor_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActor_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActor_Weapon::Equip()
{
	AAcmeCharacter* Character = Cast<AAcmeCharacter>(GetOwner());
	if (!Character) return;

	Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
}

void AActor_Weapon::Dismantle()
{
	AAcmeCharacter* Character = Cast<AAcmeCharacter>(GetOwner());
	if (!Character) return;

	Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BackSocket);
}

void AActor_Weapon::PlaySound()
{
	AudioComp->SetSound(SFXList[CurrentType]);
	AudioComp->Play();
}

FVector AActor_Weapon::GetWeponTopPos()
{
	return Mesh->GetSocketLocation(WeaponTopName);
}

FVector AActor_Weapon::GetWeponEndPos()
{
	return Mesh->GetSocketLocation(WeaponEndName);
}
