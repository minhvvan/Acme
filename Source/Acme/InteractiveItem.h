// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorInteractive.h"
#include "Acme/Utils/GlobalEnum.h"
#include "Acme/Utils/GlobalStruct.h"
#include "InteractiveItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AInteractiveItem : public AActorInteractive
{
	GENERATED_BODY()
	
public:
	AInteractiveItem();

	UFUNCTION()
	void Init(EItemName itemKey, EItemCategory category);

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<EItemName, UStaticMesh*> Meshes;

	virtual void Interact() override;

	UPROPERTY(EditAnywhere);
	FItem ItemInfo;


public:
	UFUNCTION()
	UStaticMeshComponent* GetMesh() { return Mesh; };
};
