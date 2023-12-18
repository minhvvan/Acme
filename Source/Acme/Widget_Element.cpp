// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Element.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWidget_Element::SetElementImage(EElement element)
{
	ImgElement->SetBrushFromTexture(ElementImages[element]);
}

void UWidget_Element::SetKeyImage(int Key)
{
	ImgKey->SetBrushFromTexture(KeyImages[Key]);
}

void UWidget_Element::SetTxtNum(int num)
{
	TxtNum->SetText(FText::AsNumber(num));
}
