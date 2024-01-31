// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Acme/Utils/GlobalEnum.h"
#include "DefaultItem.generated.h"

UCLASS()
class ACME_API ADefaultItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultItem();

protected:
	UPROPERTY(EditAnywhere, Category = Default)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Default)
	class USphereComponent* OverlapComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, Category = Default)
	EItemName Name;

	UPROPERTY(VisibleAnywhere, Category = Default)
	class AAcmeCharacter* OverlapedCharacter;

	UPROPERTY(VisibleAnywhere, Category = Default)
	bool bCanOverlap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetName(EItemName newName);

	UFUNCTION()
	void SetbCanOverlap(bool canOverlap);

	UFUNCTION()
	void AttachHand();

	UFUNCTION()
	void AttachBack();

	UFUNCTION()
	virtual void Active();
};
