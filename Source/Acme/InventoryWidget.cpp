// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "AcmeCharacter.h"
#include "Util.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;
	SetKeyboardFocus();
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Tab)
	{
		AAcmeCharacter* Character = GetOwningPlayerPawn<AAcmeCharacter>();
		Character->CloseInventory();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
