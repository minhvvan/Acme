// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/DraggedItemWidget.h"
#include "Components/Image.h"
#include "Acme/Utils/Util.h"

void UDraggedItemWidget::NativeOnInitialized()
{
	if (!Texture)
	{
		ImgItem->SetBrushFromTexture(Texture);
		UUtil::DebugPrint("Image");
	}
}

void UDraggedItemWidget::SetImage(UTexture2D* Tex)
{
	if (!Tex) return;
	Texture = Tex;
}
