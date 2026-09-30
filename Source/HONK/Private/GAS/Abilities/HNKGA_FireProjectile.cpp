// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HNKGA_FireProjectile.h"

#include "Inventory/Projectile/HNKProjectile.h"

UHNKGA_FireProjectile::UHNKGA_FireProjectile()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UHNKGA_FireProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	
	SpawnProjectile();
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}

AHNKProjectile* UHNKGA_FireProjectile::SpawnProjectile()
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
	
	return World->SpawnActor<AHNKProjectile>(ProjectileClass->GetClass());
}
