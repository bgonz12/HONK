// Fill out your copyright notice in the Description page of Project S.ettings.

#include "Inventory/Projectile/HNKProjectile.h"

// HONK Includes

// Engine Includes
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AHNKProjectile::AHNKProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(FName("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(FName("Projectile"));
	CollisionComponent->InitSphereRadius(50.f);
	SetRootComponent(CollisionComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->MaxSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

void AHNKProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorHit.AddDynamic(this, &AHNKProjectile::ActorHit);
}

void AHNKProjectile::ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileImpact(Hit);
}

void AHNKProjectile::ProjectileImpact(const FHitResult& Hit)
{
	FString HitActorName = Hit.GetActor() ? Hit.GetActor()->GetName() : TEXT("");
	FString HitComponentName = Hit.GetComponent() ? Hit.GetComponent()->GetName() : TEXT("");
	UE_LOG(LogTemp, Warning, TEXT("Projectile Impact: %s HitActor: %s HitComponent: %s"), *GetName(), *HitActorName, *HitComponentName);
	
	Destroy();
}

USphereComponent* AHNKProjectile::GetCollisionComponent() const
{
	return CollisionComponent;
}
