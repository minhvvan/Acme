// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementInventoryWidget.h"
#include "AcmeCharacter.h"
#include "Components/Image.h"
#include "Util.h"

void UElementInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UUtil::DebugPrint("NativeConstruct");
}

void UElementInventoryWidget::UpdateInfo()
{
	//TODO: DO Something
	auto Elements = Cast<AAcmeCharacter>(GetOwningPlayerPawn())->GetElements();

	ImgElement1->SetBrushFromTexture(ElementImages[Elements[0]]);
	ImgElement2->SetBrushFromTexture(ElementImages[Elements[1]]);
	ImgElement3->SetBrushFromTexture(ElementImages[Elements[2]]);
	ImgElement4->SetBrushFromTexture(ElementImages[Elements[3]]);

}
