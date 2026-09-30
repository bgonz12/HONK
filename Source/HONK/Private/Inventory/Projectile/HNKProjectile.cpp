// Fill out your copyright notice in the Description page of Project Settings.


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
	CollisionComponent->SetCollisionProfileName(FName("BlockAllDynamic"));
	CollisionComponent->InitSphereRadius(50.f);
	SetRootComponent(CollisionComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->MaxSpeed = 2000.f;
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
}

