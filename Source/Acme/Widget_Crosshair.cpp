// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Crosshair.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"

void UWidget_Crosshair::SetPercent(float percent)
{
	if (!IsValid(MatInst))
	{
		MatInst = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), PercentMaterial);
		PB_Charge->SetBrushFromMaterial(MatInst);
	}

	MatInst->SetScalarParameterValue(FName(TEXT("Percentage")), percent);
}

void UWidget_Crosshair::SetColor(FColor color)
{
	if (!IsValid(MatInst))
	{
		MatInst = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), PercentMaterial);
		PB_Charge->SetBrushFromMaterial(MatInst);
	}

	MatInst->SetVectorParameterValue(FName(TEXT("Color")), color);
}
