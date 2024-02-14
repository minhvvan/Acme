// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultItem.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "AcmeCharacter.h"
#include "Acme/Widget/WidgetIndicator.h"
#include "Acme/Utils/Util.h"
#include "Acme/Utils/GlobalConst.h"

// Sets default values
ADefaultItem::ADefaultItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(RootComponent);
	OverlapComp->InitSphereRadius(100.f);

}

// Called when the game starts or when spawned
void ADefaultItem::BeginPlay()
{
	Super::BeginPlay();

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ADefaultItem::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &ADefaultItem::OnEndOverlap);
}

void ADefaultItem::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlapedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlapedCharacter) return;

	}
}

void ADefaultItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlapedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlapedCharacter) return;

	}
}

// Called every frame
void ADefaultItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultItem::SetName(EItemName newName)
{
	Name = newName;
}


void ADefaultItem::AttachHand()
{
	AAcmeCharacter* Character = Cast<AAcmeCharacter>(GetOwner());
	if (!Character) return;

	Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GlobalConst::HandSocket);
}

void ADefaultItem::AttachBack()
{
	AAcmeCharacter* Character = Cast<AAcmeCharacter>(GetOwner());
	if (!Character) return;

	Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GlobalConst::BackSocket);
}

void ADefaultItem::Active()
{
	//override
}
