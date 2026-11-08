// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Projectile/HNKProjectileFireComponent.h"

// HONK Includes
#include "Character/HNKCharacter.h"
#include "Inventory/Projectile/HNKProjectile.h"

// Engine Includes
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

UHNKProjectileFireComponent::UHNKProjectileFireComponent()
{
	SetIsReplicatedByDefault(true);
}

AHNKProjectile* UHNKProjectileFireComponent::SpawnProjectile(TSubclassOf<AHNKProjectile> ProjectileClass, const FTransform& SpawnTransform)
{
	if (!ProjectileClass)
	{
		return nullptr;
	}
	
	UWorld* World = GetWorld();
	if (!World)
	{
		return nullptr;
	}
	
	AHNKCharacter* Character = Cast<AHNKCharacter>(GetOwner());
	if (!Character)
	{
		return nullptr;
	}
	
	// Note: Controller might not be available from simulated proxy
	AController* Controller = Character->GetController();

	if (AHNKProjectile* Projectile = World->SpawnActorDeferred<AHNKProjectile>(ProjectileClass, SpawnTransform, Controller, Character, ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
	{
		if (UCapsuleComponent* CapsuleComponent = Character->GetCapsuleComponent())
		{
			CapsuleComponent->IgnoreActorWhenMoving(Projectile, true);
		}
		
		if (USphereComponent* CollisionComponent = Projectile->GetCollisionComponent())
		{
			CollisionComponent->IgnoreActorWhenMoving(Character, true);
		}
		
		Projectile->FinishSpawning(SpawnTransform);
		return Projectile;
	}
	
	return nullptr;
}

void UHNKProjectileFireComponent::Multicast_SpawnProjectile_Implementation(TSubclassOf<AHNKProjectile> ProjectileClass, const FTransform& SpawnTransform)
{
	// Don't spawn projectile on owning clients, as it should already be predictively spawned
	if (GetNetMode() == ENetMode::NM_Client && GetOwnerRole() == ROLE_AutonomousProxy)
	{
		return;
	}
	
	SpawnProjectile(ProjectileClass, SpawnTransform);
}
