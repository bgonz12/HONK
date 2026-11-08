// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "Components/ActorComponent.h"

#include "HNKProjectileFireComponent.generated.h"

class AHNKProjectile;

/**
 * Handles spawning locally simulated projectiles over the network. 
 */
UCLASS()
class HONK_API UHNKProjectileFireComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UHNKProjectileFireComponent();
	
	UFUNCTION()
	AHNKProjectile* SpawnProjectile(TSubclassOf<AHNKProjectile> ProjectileClass, const FTransform& SpawnTransform);
	
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SpawnProjectile(TSubclassOf<AHNKProjectile> ProjectileClass, const FTransform& SpawnTransform);
};
