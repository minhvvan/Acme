// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/DetailActionInnerWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Acme/Utils/Util.h"
#include "Acme/Utils/GlobalConst.h"

void UDetailActionInnerWidget::NativeOnInitialized()
{
	BtnAction->OnClicked.AddDynamic(this, &UDetailActionInnerWidget::OnClicked);
}

void UDetailActionInnerWidget::OnClicked()
{
	//TODO: 함수로 뺴자
	switch (DetailAction)
	{
	case EDetailAction::E_Equip:
		UUtil::DebugPrint("Equip");
		break;
	case EDetailAction::E_Dismantle:
		UUtil::DebugPrint("E_Dismantle");
		break;
	case EDetailAction::E_Consume:
		UUtil::DebugPrint("E_Consume");
		break;
	case EDetailAction::E_Dump:
		UUtil::DebugPrint("E_Dump");
		break;
	}

	DelegateOnClicked.Broadcast();
}

void UDetailActionInnerWidget::Init(EDetailAction action)
{
	DetailAction = action;

	switch (action)
	{
	case EDetailAction::E_Equip:
		TxtAction->SetText(FText::FromString(GlobalConst::EquipActionName));
		break;
	case EDetailAction::E_Dismantle:
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
