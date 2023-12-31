// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementItemWidget.h"
#include "ElementData.h"
#include "Components/Image.h"
#include "Util.h"

void UElementItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UElementData* Data = Cast<UElementData>(ListItemObject);
	EElement element = Data->GetElement();

	if (!ElementImg[element]) return;
	ImgElement->SetBrushFromTexture(ElementImg[element]);
}

void UElementItemWidget::PlayReactionAnim()
{
	//if (!ElementReactionAnim) return;
	OnReactionAnimEnd.Clear();
	OnReactionAnimEnd.BindDynamic(this, &UElementItemWidget::OnRecationAnimEnd);

	BindToAnimationFinished(ElementReactionAnim, OnReactionAnimEnd);
	PlayAnimation(ElementReactionAnim);
}

void UElementItemWidget::OnRecationAnimEnd()
{
	OnAnimEnd.Broadcast();
}
