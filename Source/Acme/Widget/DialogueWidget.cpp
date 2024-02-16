// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/DialogueWidget.h"
#include "Acme/AcmeCharacter.h"
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
}

void UDialogueWidget::OnLeavedAccept()
{
	if (AnimHoverAccept) PlayAnimationReverse(AnimHoverAccept);
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
	auto PC = GetOwningPlayer();
	if (!PC) return;

	if (!Player) Player = Cast<AAcmeCharacter>(PC->GetCharacter());
	Player->AddQuest(Quest);

	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;

	RemoveFromParent();
}

void UDialogueWidget::OnClickedReject()
{
	auto PC = GetOwningPlayer();
	if (!PC) return;

	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;

	RemoveFromParent();
}

void UDialogueWidget::SetQuestInfo(FQuest newQuest)
{
	Quest = newQuest;
}