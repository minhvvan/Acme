// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/AlchemicComposeWidget.h"
#include "Acme/AcmeCharacter.h"

void UAlchemicComposeWidget::NativeConstruct()
{
	bIsFocusable = true;
	SetKeyboardFocus();
}

FReply UAlchemicComposeWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	//TODO: Change Key
	if (InKeyEvent.GetKey() == EKeys::End)
	{
		AAcmeCharacter* Character = GetOwningPlayerPawn<AAcmeCharacter>();
		Character->CloseInteractWidget();
	}

	return Result;
}
