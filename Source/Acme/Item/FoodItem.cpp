// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Item/FoodItem.h"
#include "Acme/Utils/Util.h"
#include "Acme/AcmeCharacter.h"

void AFoodItem::BeginPlay()
{
	//TODO: Data�� ������ ��
	Satiety = 10;
}

void AFoodItem::Active()
{
	//TODO:Play Anim

	Player->ConsumeItemQuick();
	Player->AddSatiety(Satiety);
}
