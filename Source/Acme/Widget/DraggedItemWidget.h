// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggedItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API UDraggedItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgItem;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* Texture;

	virtual void NativeOnInitialized();

public:
	UFUNCTION()
	void SetImage(UTexture2D* Tex);
};
