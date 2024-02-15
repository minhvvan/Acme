// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Animation/WidgetAnimation.h"
#include "Acme/Utils/Util.h"

void UDialogueWidget::NativeOnInitialized()
{
	BtnAccept->OnHovered.AddDynamic(this, &UDialogueWidget::OnHoveredAccept);
	BtnAccept->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnLeavedAccept);	
	BtnAccept->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedAccept);
	
	BtnReject->OnHovered.AddDynamic(this, &UDialogueWidget::OnHoveredReject);
	BtnReject->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnLeavedReject);
	BtnReject->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedReject);
}

void UDialogueWidget::OnHoveredAccept()
{
	if (AnimHoverAccept) PlayAnimation(AnimHoverAccept);
	UUtil::DebugPrint("Hover");
}

void UDialogueWidget::OnLeavedAccept()
{
	if (AnimHoverAccept) PlayAnimationReverse(AnimHoverAccept);
	UUtil::DebugPrint("Leave");
}

void UDialogueWidget::OnHoveredReject()
{
	if (AnimHoverReject) PlayAnimation(AnimHoverReject);
}

void UDialogueWidget::OnLeavedReject()
{
	if (AnimHoverReject) PlayAnimationReverse(AnimHoverReject);
}

void UDialogueWidget::OnClickedAccept()
{

}

void UDialogueWidget::OnClickedReject()
{
}
