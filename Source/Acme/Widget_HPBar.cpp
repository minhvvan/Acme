// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_HPBar.h"
#include "Components/ProgressBar.h"
#include "Components/TileView.h"
#include "MonsterStatComponent.h"
#include "ElementData.h"
#include "ElementItemWidget.h"
#include "Util.h"

void UWidget_HPBar::SetHPPercent(int CurrentHP, int MaxHP)
{
	float percent = float(CurrentHP) / MaxHP;

	TargetPercent = percent;
}

void UWidget_HPBar::BindDelegate(UMonsterStatComponent* StatComp)
{
	StatComp->OnChangedHP.AddUObject(this, &UWidget_HPBar::SetHPPercent);
}

void UWidget_HPBar::AddElement(EElement element)
{
	UElementData* Data = NewObject<UElementData>();
	Data->SetElement(element);

	TV_Element->AddItem(Data);
}

void UWidget_HPBar::PopTwoElement()
{
	UUtil::DebugPrint("PopElement");

	auto LastItemWidget = Cast<UElementItemWidget>(TV_Element->GetEntryWidgetFromItem(TV_Element->GetItemAt(TV_Element->GetNumItems() - 1)));
	auto SecondItemWidget = Cast<UElementItemWidget>(TV_Element->GetEntryWidgetFromItem(TV_Element->GetItemAt(TV_Element->GetNumItems() - 2)));

	SecondItemWidget->OnAnimEnd.AddUObject(this, &UWidget_HPBar::RemoveLastItem);
	
	LastItemWidget->PlayReactionAnim();	
	SecondItemWidget->PlayReactionAnim();
}

void UWidget_HPBar::RemoveLastItem()
{
	auto SecondItemWidget = Cast<UElementItemWidget>(TV_Element->GetEntryWidgetFromItem(TV_Element->GetItemAt(TV_Element->GetNumItems() - 2)));
	SecondItemWidget->OnAnimEnd.RemoveAll(this);

	TV_Element->RemoveItem(TV_Element->GetItemAt(TV_Element->GetNumItems() - 1));
	TV_Element->RemoveItem(TV_Element->GetItemAt(TV_Element->GetNumItems() - 1));
	UUtil::DebugPrint("RemoveLastItem");
}

void UWidget_HPBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (PB_HP->GetPercent() != TargetPercent)
	{
		float interpolated = FMath::Lerp(PB_HP->GetPercent(), TargetPercent, .7f);

		PB_HP->SetPercent(interpolated);
	}
}
