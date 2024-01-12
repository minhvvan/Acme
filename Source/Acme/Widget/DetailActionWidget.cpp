// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/DetailActionWidget.h"
#include "Components/VerticalBox.h"
#include "Acme/Widget/DetailActionInnerWidget.h"

void UDetailActionWidget::SetInnerWidget(FItem& item, int idx)
{
	ItemInfo = item;
	Index = idx;

	switch (ItemInfo.Category)
	{
	case EItemCategory::E_Element:
		CreateDump();
		break;
	case EItemCategory::E_Equipment:
		if (ItemInfo.Equiped == true) CreateUnEquip();
		else CreateEquip();
		CreateDump();
		break;
	case EItemCategory::E_Tool:
		CreateInstall();
		CreateDump();
		break;
	case EItemCategory::E_Potion:
		CreateConsume();
		CreateDump();
		break;
	case EItemCategory::E_Food:
		CreateConsume();
		CreateDump();
		break;
	case EItemCategory::E_Material:
		CreateDump();
		break;
	}
}

void UDetailActionWidget::CreateEquip()
{
	UDetailActionInnerWidget* Detail = Cast<UDetailActionInnerWidget>(CreateWidget(GetWorld(), DetailInnerWidgetClass));
	if (!Detail) return;
	
	Detail->Init(EDetailAction::E_Equip, ItemInfo.Category, Index);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CreateUnEquip()
{
	UDetailActionInnerWidget* Detail = Cast<UDetailActionInnerWidget>(CreateWidget(GetWorld(), DetailInnerWidgetClass));
	if (!Detail) return;

	Detail->Init(EDetailAction::E_Unequip, ItemInfo.Category, Index);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CreateConsume()
{
	UDetailActionInnerWidget* Detail = Cast<UDetailActionInnerWidget>(CreateWidget(GetWorld(), DetailInnerWidgetClass));
	if (!Detail) return;

	Detail->Init(EDetailAction::E_Consume, ItemInfo.Category, Index);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CreateDump()
{
	UDetailActionInnerWidget* Detail = Cast<UDetailActionInnerWidget>(CreateWidget(GetWorld(), DetailInnerWidgetClass));
	if (!Detail) return;

	Detail->Init(EDetailAction::E_Dump, ItemInfo.Category, Index);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CreateInstall()
{
	UDetailActionInnerWidget* Detail = Cast<UDetailActionInnerWidget>(CreateWidget(GetWorld(), DetailInnerWidgetClass));
	if (!Detail) return;
	
	Detail->Init(EDetailAction::E_Install, ItemInfo.Category, Index);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CloseWidget()
{
	RemoveFromParent();
}
