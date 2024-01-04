// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Widget_Element.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UWidget_Element : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(VIsibleAnywhere, meta = (BindWidget))
	class UImage* ImgElement;

	UPROPERTY(VIsibleAnywhere, meta = (BindWidget))
	class UImage* ImgKey;

	UPROPERTY(VIsibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtNum;

public:
	UFUNCTION()
	void SetElementImage(EElement element);

	UFUNCTION()
	void SetKeyImage(int Key);

	UFUNCTION()
	void SetTxtNum(int num);	
	
	UFUNCTION()
	int GetTxtNum();

	UFUNCTION()
	EElement GetCurrentElement();

protected:
	UPROPERTY(EditAnywhere)
	TMap<EElement, UTexture2D*> ElementImages;

	UPROPERTY(EditAnywhere)
	TMap<int, UTexture2D*> KeyImages;

	UPROPERTY(VisibleAnywhere)
	EElement CurrentElement;

	UPROPERTY(VisibleAnywhere)
	int CurrentAmount;
};
