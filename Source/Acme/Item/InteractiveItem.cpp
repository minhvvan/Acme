// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Acme/Framework/AcmeGameInstance.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"

AInteractiveItem::AInteractiveItem()
{
	ItemInfo.Name = EItemName::E_Empty;
	ItemInfo.Num = 1;
	ItemInfo.Category = EItemCategory::E_End;

	Indicator = CreateDefaultSubobject<UWidgetComponent>(TEXT("Indicator"));
	Indicator->SetupAttachment(RootComponent);

	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(RootComponent);
	OverlapComp->InitSphereRadius(100.f);
}

void AInteractiveItem::Init(FItem newItem)
{
	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
	Mesh->SetStaticMesh(GameInstance->GetItemMesh(newItem.Name));

	ItemInfo = newItem;
}

void AInteractiveItem::BeginPlay()
{
	Super::BeginPlay();

	Indicator->SetVisibility(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveItem::OnBeginOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &AInteractiveItem::OnEndOverlap);
}

void AInteractiveItem::Interact()
{
	if (!OverlappedCharacter) return;

	if (OverlappedCharacter->AddItem(ItemInfo))
	{
		OnInteract.Broadcast(this);
		Destroy();
	}
}

void AInteractiveItem::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlappedCharacter) return;

		Mesh->SetRenderCustomDepth(true);
		SetVisibleIndicator(true);
	}
}

void AInteractiveItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = nullptr;

		Mesh->SetRenderCustomDepth(false);
		bCanOverlap = true;
		SetVisibleIndicator(false);
	}
}


void AInteractiveItem::SetVisibleIndicator(bool bVisible)
{
	//indicator visible set
	if (!IsValid(Indicator)) return;

	Indicator->SetVisibility(bVisible);
}