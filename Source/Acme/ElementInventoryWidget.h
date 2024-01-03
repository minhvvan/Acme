// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryInnerWidget.h"
#include "GlobalEnum.h"
#include "ElementInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UElementInventoryWidget : public UInventoryInnerWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgElement1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgElement2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgElement3;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgElement4;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgCurrentElement;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVElement;

	UPROPERTY(EditAnywhere)
	TMap<EElement, UTexture2D*> ElementImages;

	UPROPERTY(VisibleAnywhere)
	class AAcmeCharacter* OwnerCharacter;


protected:
	virtual void NativeConstruct();

public:
	virtual void UpdateInfo() override;
};
