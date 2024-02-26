// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "Acme/Interface/InteractableActor.h"
#include "PotionTrunk.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API APotionTrunk : public ABaseItem, public IInteractableActor
{
	GENERATED_BODY()
	
public:
	APotionTrunk();


protected:
	UPROPERTY(EditAnywhere, Category = Default)
	class USphereComponent* OverlapComp;

	UPROPERTY(EditAnywhere, Category = Default)
	class UWidgetComponent* Indicator;

public:
	virtual void Interact();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SetVisibleIndicator(bool bVisible);

protected:
	UPROPERTY(VisibleAnywhere, Category = Default)
	class AAcmeCharacter* OverlappedCharacter;

	UPROPERTY(EditAnywhere, Category = Widget, meta = (AllowAccessPrivate = "true"))
	TSubclassOf<class UPotionCraftWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere, Category = Widget, meta = (AllowAccessPrivate = "true"))
	UPotionCraftWidget* InteractWidget;
};
