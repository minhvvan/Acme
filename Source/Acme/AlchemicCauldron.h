// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Item/BaseItem.h"
#include "Acme/Interface/InteractableActor.h"
#include "AlchemicCauldron.generated.h"

class UAlchemicComposeWidget;

UCLASS()
class ACME_API AAlchemicCauldron : public ABaseItem, public IInteractableActor
{
	GENERATED_BODY()
	
public:
	AAlchemicCauldron();

protected:
	UPROPERTY(EditAnywhere, Category = Default)
	class USphereComponent* OverlapComp;

protected:
	UPROPERTY(EditAnywhere, Category = Widget, meta = (AllowAccessPrivate = "true"))
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere, Category = Widget, meta = (AllowAccessPrivate = "true"))
	UAlchemicComposeWidget* InteractWidget;

	UPROPERTY(VisibleAnywhere, Category = Default)
	class AAcmeCharacter* OverlappedCharacter;

	UPROPERTY(EditAnywhere, Category = Default)
	class UWidgetComponent* Indicator;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SetVisibleIndicator(bool bVisible);

public:
	virtual void Interact();

};
