// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Monster/CharacterMonster.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Acme/Component/MonsterStatComponent.h"
#include "Acme/Widget/Widget_HPBar.h"
#include "Acme/Animation/AI_Monster.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/InteractiveItem.h"
#include "Acme/Utils/Util.h"
#include "MonsterAIController.h"


// Sets default values
ACharacterMonster::ACharacterMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatCompoenent = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("Stat"));

	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->SetupAttachment(RootComponent);

	IsCombat = false;
	CombatSustainTime = 5.f;

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ACharacterMonster::BeginPlay()
{
	Super::BeginPlay();
	
	InitState();

	AnimInstance = Cast<UAI_Monster>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &ACharacterMonster::OnMontageEnd);
}

// Called every frame
void ACharacterMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterMonster::OnAttacked(int damage, EElement ElementType)
{
	if (!HPBar) return;
	if (!AnimInstance) return;

	IsCombat = true;
	HPBar->SetVisibility(true);

	AnimInstance->PlayAttacked();

	GetWorldTimerManager().SetTimer(CombatTimer, FTimerDelegate::CreateLambda(
		[this]() {
			IsCombat = false;
			HPBar->SetVisibility(false);
			//TODO: 전투 종료, 제자리로 돌아가게
		}), CombatSustainTime, false);

	TakeDamage(damage);
}

void ACharacterMonster::Attack()
{
	IsCombat = true;
	HPBar->SetVisibility(true);

}

void ACharacterMonster::InitState()
{
	auto HpBar = Cast<UWidget_HPBar>(HPBar->GetWidget());
	HpBar->BindDelegate(StatCompoenent);
	HpBar->SetHPPercent(100, 100);

	HPBar->SetVisibility(false);
}

void ACharacterMonster::Die()
{
	AnimInstance->PlayDeath();
}

void ACharacterMonster::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	FString MontageName = Montage->GetName();

	if (MontageName == TEXT("AM_Attacked"))
	{

	}
	else if (MontageName == TEXT("AM_Death_Monster"))
	{
		Destroy();
		OnDied.Broadcast();

		//TODO: fx,Item Drop
		if (ItemClass == nullptr) return;

		FVector SpawnPos = GetActorLocation();
		SpawnPos.Z += 10;

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AInteractiveItem* DropItem = GetWorld()->SpawnActor<AInteractiveItem>(ItemClass, FTransform(FRotator::ZeroRotator, SpawnPos), SpawnParam);
		DropItem->Init(EItemName::E_Cube, EItemCategory::E_Material);
		DropItem->SetbCanOverlap(true);
	}
}

void ACharacterMonster::SetTarget(AAcmeCharacter* target)
{
	TargetCharacter = target;
}

bool ACharacterMonster::GetIsAttack()
{
	return IsAttacked;
}

void ACharacterMonster::SetIsAttack(bool bIsAttack)
{
	IsAttacked = bIsAttack;
}

void ACharacterMonster::TakeDamage(int damage)
{
	int CurrentHP = StatCompoenent->GetCurrentHP();
	int newHP = CurrentHP - damage;

	if (newHP < 0) newHP = 0;
	StatCompoenent->SetCurrentHP(newHP);

	if (newHP == 0) Die();
}

void ACharacterMonster::OnFrozen()
{
	//frozen되면 처형 가능 -> 최대체력 n%
}

void ACharacterMonster::OnElectricShock()
{
	//감전상태에서 붙으면 감전
}

void ACharacterMonster::OnBurn()
{
	//n초간 지속적인 피해 
}

void ACharacterMonster::KnockBack(float dist)
{
	//dist만큼 넉백
	if (TargetCharacter == nullptr) return;

	FVector CurrentPos = GetActorLocation();
	FVector TargetPos = TargetCharacter.Get()->GetActorLocation();

	FVector Dir = (CurrentPos - TargetPos);
	LaunchCharacter(Dir * dist, false, false);
}
