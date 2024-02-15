// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Acme/AcmeGameInstance.h"
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
	//Info Setting
	//TODO: GI -> GetMesh
	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(GetGameInstance());
	Mesh->SetStaticMesh(GameInstance->GetItemMesh(newItem.Name));

	ItemInfo.Name = newItem.Name;
	ItemInfo.Num = 1;
	ItemInfo.Category = newItem.Category;
	ItemInfo.Part = newItem.Part;
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
	//DropItem -> Player
	if (!OverlappedCharacter) return;

	if (OverlappedCharacter->AddItem(ItemInfo))
	{
		UUtil::DebugPrint("Inter");
		Destroy();
	}
}

void AInteractiveItem::OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = Cast<AAcmeCharacter>(OtherActor);
		if (!OverlappedCharacter) return;

		SetVisibleIndicator(true);
	}
}

void AInteractiveItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherComp != nullptr)
	{
		OverlappedCharacter = nullptr;

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