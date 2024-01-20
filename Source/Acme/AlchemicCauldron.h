// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorInteractive.h"
#include "AlchemicCauldron.generated.h"

class UAlchemicComposeWidget;

UCLASS()
class ACME_API AAlchemicCauldron : public AActorInteractive
{
	GENERATED_BODY()
	
public:
	AAlchemicCauldron();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Widget, meta = (AllowAccessPrivate = "true"))
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere, Category = Widget, meta = (AllowAccessPrivate = "true"))
	UAlchemicComposeWidget* InteractWidget;

public:
	virtual void Interact();

};
