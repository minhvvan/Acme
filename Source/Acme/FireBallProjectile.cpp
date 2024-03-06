// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBallProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "FireArea.h"
#include "Acme/Utils/Util.h"


// Sets default values
AFireBallProjectile::AFireBallProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    if (!CollisionComponent)
    {
        // Use a sphere as a simple collision representation.
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        // Set the sphere's collision radius.
        CollisionComponent->InitSphereRadius(15.0f);
        // Set the root component to be the collision component.
        RootComponent = CollisionComponent;
    }

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

    if (!ProjectileMovement)
    {
        // Use this component to drive this projectile's movement.
        ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovement->SetUpdatedComponent(CollisionComponent);
        ProjectileMovement->InitialSpeed = 3000.0f;
        ProjectileMovement->MaxSpeed = 3000.0f;
        ProjectileMovement->bRotationFollowsVelocity = true;
        ProjectileMovement->bShouldBounce = true;
        ProjectileMovement->Bounciness = 0.3f;
        ProjectileMovement->ProjectileGravityScale = 0.0f;
    }

    bHit = false;
}

// Called when the game starts or when spawned
void AFireBallProjectile::BeginPlay()
{
	Super::BeginPlay();
	
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFireBallProjectile::OnBeginOverlap);
    ProjectileMovement->OnProjectileStop.AddDynamic(this, &AFireBallProjectile::SpawnFireArea);
}

void AFireBallProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OverlappedComponent)
    {
        if (GetInstigator() != OtherActor)
        {
            FHitResult Result;

            FVector Start = OtherActor->GetActorLocation();
            FVector End = Start;
            End.Z -= 100;

            bool bResult = GetWorld()->LineTraceSingleByChannel(OUT Result, Start, End, ECollisionChannel::ECC_Visibility);
            if (bResult)
            {
                SpawnFireArea(Result);
                bHit = true;
            }
        }
    }
}

// Called every frame
void AFireBallProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireBallProjectile::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}

void AFireBallProjectile::SpawnFireArea(const FHitResult& ImpactResult)
{
    if (bHit) return;
    bHit = true;

    Mesh->SetVisibility(false);

    //Actor 생성 시간 지나면 소멸
    if (!FireAreaClass) return;

    FActorSpawnParameters param;
    param.Instigator = GetInstigator();

    FVector Loc = ImpactResult.ImpactPoint;
    GetWorld()->SpawnActor<AFireArea>(FireAreaClass, Loc, FRotator::ZeroRotator, param);
}

