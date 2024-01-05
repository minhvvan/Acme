// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveElement.h"
#include "AcmeCharacter.h"
#include "Acme/Widget/WidgetIndicator.h"
#include "Components/WidgetComponent.h"

AInteractiveElement::AInteractiveElement()
{
	ElementType = EElement::E_End;
}

void AInteractiveElement::SetElementType(EElement element)
{
	ElementType = element;
}

void AInteractiveElement::Interact()
{
	//OverlapedCharacter
	OverlapedCharacter->AddElement(ElementType);
	Destroy();
}
