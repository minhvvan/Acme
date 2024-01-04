// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorInteractive.h"
#include "Acme/Utils/GlobalEnum.h"
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
	void Init(EItemName itemKey);

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<EItemName, UStaticMesh*> Meshes;

};
