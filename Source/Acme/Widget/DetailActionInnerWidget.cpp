// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/DetailActionInnerWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Utils/Util.h"
#include "Acme/Utils/GlobalConst.h"

void UDetailActionInnerWidget::NativeOnInitialized()
{
	BtnAction->OnClicked.AddDynamic(this, &UDetailActionInnerWidget::OnClicked);
}

void UDetailActionInnerWidget::OnClicked()
{
	switch (DetailAction)
	{
	case EDetailAction::E_Equip:
		Equip();
		break;
	case EDetailAction::E_Unequip:
		Unequip();
		break;
	case EDetailAction::E_Consume:
		Consume();
		break;
	case EDetailAction::E_Dump:
		Dump();
		break;
	}

	DelegateOnClicked.Broadcast();
}

void UDetailActionInnerWidget::Equip()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	Player->Equip(Index);
}

void UDetailActionInnerWidget::Unequip()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	Player->Unequip(Index);
}

void UDetailActionInnerWidget::Consume()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	//Player->Consume(Index);
}

void UDetailActionInnerWidget::Dump()
{
	if (!Player) Player = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	//Player->Dump(ItemCategory, Index);
}

void UDetailActionInnerWidget::Init(EDetailAction action, EItemCategory category, int idx)
{
	DetailAction = action;
	ItemCategory = category;
	Index = idx;

	switch (action)
	{
	case EDetailAction::E_Equip:
		TxtAction->SetText(FText::FromString(GlobalConst::EquipActionName));
		break;
	case EDetailAction::E_Unequip:
		TxtAction->SetText(FText::FromString(GlobalConst::DismantleActionName));
		break;
	case EDetailAction::E_Install:
		TxtAction->SetText(FText::FromString(GlobalConst::InstallActionName));
		break;
	case EDetailAction::E_Consume:
		TxtAction->SetText(FText::FromString(GlobalConst::ConsumeActionName));
		break;
	case EDetailAction::E_Dump:
		TxtAction->SetText(FText::FromString(GlobalConst::DumpActionName));
		break;
	}
}
