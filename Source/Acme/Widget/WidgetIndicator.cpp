// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetIndicator.h"
#include "Components/TextBlock.h"

void UWidgetIndicator::SetName(FString name)
{
	if (name.IsEmpty()) return;
	if (!TxtName) return;
	TxtName->SetText(FText::FromString(name));
}
