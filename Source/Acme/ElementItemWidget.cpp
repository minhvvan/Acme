// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementItemWidget.h"
#include "ElementData.h"
#include "Components/Image.h"
#include "Util.h"

void UElementItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UElementData* Data = Cast<UElementData>(ListItemObject);
	EElement element = Data->GetElement();


	switch (element)
	{
	case EElement::E_Fire:
		UUtil::DebugPrint("Fire");
		break;
	case EElement::E_Water:
		UUtil::DebugPrint("Water");
		break;
	case EElement::E_Earth:
		UUtil::DebugPrint("Earth");
		break;
	case EElement::E_Air:
		UUtil::DebugPrint("Air");
		break;
	case EElement::E_Ice:
		UUtil::DebugPrint("Ice");
		break;
	case EElement::E_Thunder:
		UUtil::DebugPrint("Thunder");
		break;
	case EElement::E_Normal:
		UUtil::DebugPrint("Normal");
		break;
	}


	if (!ElementImg[element]) return;
	ImgElement->SetBrushFromTexture(ElementImg[element]);
}