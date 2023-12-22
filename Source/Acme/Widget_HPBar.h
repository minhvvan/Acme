// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HPBar.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UWidget_HPBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UProgressBar* PB_HP;


public:
	UFUNCTION()
	void SetHPPercent(int CurrentHP, int MaxHP);

	UFUNCTION()
	void BindDelegate(class UAC_Stat* StatComp);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY(VisibleAnywhere)
	float TargetPercent;
};
