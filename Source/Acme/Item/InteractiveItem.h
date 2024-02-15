// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Acme/Interface/InteractableActor.h"
#include "InteractiveItem.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API AInteractiveItem : public ABaseItem, public IInteractableActor
{
	GENERATED_BODY()
	
public:
	AInteractiveItem();

	UFUNCTION()
	void Init(FItem newItem);

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<EItemName, UStaticMesh*> Meshes;

	UPROPERTY(EditAnywhere, Category = Default)
	class USphereComponent* OverlapComp;

	UPROPERTY(EditAnywhere, Category = Default)
	class UWidgetComponent* Indicator;

protected:
	virtual void BeginPlay() override;

	virtual void Interact() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SetVisibleIndicator(bool bVisible);

protected:
	UPROPERTY(EditAnywhere);
	FItem ItemInfo;

	UPROPERTY(VisibleAnywhere, Category = Default)
	class AAcmeCharacter* OverlappedCharacter;

	UPROPERTY(VisibleAnywhere, Category = Default)
	class UAcmeGameInstance* GameInstance;

	UPROPERTY(VisibleAnywhere, Category = Default)
	bool bCanOverlap;

public:
	UFUNCTION()
	UStaticMeshComponent* GetMesh() { return Mesh; };
};
