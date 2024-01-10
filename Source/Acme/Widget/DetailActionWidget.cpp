// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/DetailActionWidget.h"
#include "Components/VerticalBox.h"
#include "Acme/Widget/DetailActionInnerWidget.h"

void UDetailActionWidget::SetInnerWidget(EItemCategory category)
{
	switch (category)
	{
	case EItemCategory::E_Element:
		CreateDump();
		break;
	case EItemCategory::E_Equipment:
		CreateEquip();
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
	
	Detail->Init(EDetailAction::E_Equip);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CreateDismantle()
{
	UDetailActionInnerWidget* Detail = Cast<UDetailActionInnerWidget>(CreateWidget(GetWorld(), DetailInnerWidgetClass));
	if (!Detail) return;

	Detail->Init(EDetailAction::E_Dismantle);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CreateConsume()
{
	UDetailActionInnerWidget* Detail = Cast<UDetailActionInnerWidget>(CreateWidget(GetWorld(), DetailInnerWidgetClass));
	if (!Detail) return;

	Detail->Init(EDetailAction::E_Consume);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CreateDump()
{
	UDetailActionInnerWidget* Detail = Cast<UDetailActionInnerWidget>(CreateWidget(GetWorld(), DetailInnerWidgetClass));
	if (!Detail) return;

	Detail->Init(EDetailAction::E_Dump);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CreateInstall()
{
	UDetailActionInnerWidget* Detail = Cast<UDetailActionInnerWidget>(CreateWidget(GetWorld(), DetailInnerWidgetClass));
	if (!Detail) return;
	
	Detail->Init(EDetailAction::E_Install);
	Detail->DelegateOnClicked.AddUObject(this, &UDetailActionWidget::CloseWidget);
	VertAction->AddChild(Detail);
}

void UDetailActionWidget::CloseWidget()
{
	RemoveFromParent();
}
