// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GlobalEnum.h"
#include "ElementItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UElementItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgElement;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(VisibleAnywhere)
	EElement Element;

	UPROPERTY(EditAnywhere)
	TMap<EElement, UTexture2D*> ElementImg;
};
