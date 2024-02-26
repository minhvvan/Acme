// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Item/PotionItem.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"

void APotionItem::Active()
{
	Player->ConsumeItemQuick();

	Player->Heal(10);
}
