// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Acme/Utils/GlobalEnum.h"
#include "ActorInteractive.generated.h"

UCLASS()
class ACME_API AActorInteractive : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorInteractive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Default)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Default)
	class USphereComponent* OverlapComp;

	UPROPERTY(EditAnywhere, Category = Default)
	class UWidgetComponent* Indicator;

	UPROPERTY(VisibleAnywhere, Category = Default)
	class AAcmeCharacter* OverlapedCharacter;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = Default)
	EItemName Name;

	UPROPERTY(VisibleAnywhere, Category = Default)
	bool bCanInteract;

	UPROPERTY(VisibleAnywhere, Category = Default)
	bool bCanOverlap;

	UPROPERTY(EditAnywhere, Category = Default)
	TMap<EItemName, FString> NameStrings;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetVisibleIndicator(bool bVisible);

	UFUNCTION()
	virtual void Interact();

	UFUNCTION()
	void SetName(EItemName newName);

	UFUNCTION()
	bool GetbCanInteract();

	UFUNCTION()
	void SetbCanInteract(bool canInteract);

	UFUNCTION()
	void SetbCanOverlap(bool canOverlap);
};
