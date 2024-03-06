// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Acme/Monster/CharacterMonster.h"
#include "Acme/FireBallProjectile.h"
#include "BossMonster.generated.h"

/**
 * 
 */

UCLASS()
class ACME_API ABossMonster : public ACharacterMonster
{
	GENERATED_BODY()

public:
	ABossMonster();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UBossAnimInstance* BossAnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class ABossAIController* BossAIController;

protected:
	virtual void BeginPlay() override;

	virtual void FinishCombat();

	virtual void Tick(float DeltaSeconds);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFireBallProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MouthOffset;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove;

	UPROPERTY(VisibleAnywhere)
	FVector TargetPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Dist;

public:
	virtual void OnAttacked(int damage) override;

	UFUNCTION()
	void Fire(); 

	UFUNCTION()
	void Bite();

	UFUNCTION()
	void Move();

	UFUNCTION()
	void TailAttack();

	UFUNCTION()
	void FlyFire();

	UFUNCTION()
	void BiteAttackCheck();

	UFUNCTION()
	void FireBall();
};
