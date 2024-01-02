// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorInteractive.h"
#include "GlobalEnum.h"
#include "InteractiveItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AInteractiveItem : public AActorInteractive
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Init(EItem itemKey);

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<EItem, UStaticMesh*> Meshes;

};
