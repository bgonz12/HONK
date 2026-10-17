// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HNKGameplayAbility_FireProjectile.h"

#include "Character/HNKCharacter.h"
#include "Inventory/Projectile/HNKProjectile.h"

UHNKGameplayAbility_FireProjectile::UHNKGameplayAbility_FireProjectile()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UHNKGameplayAbility_FireProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{	
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	FTransform SpawnTransform = FTransform::Identity;
	GetSpawnTransform(SpawnTransform);
	
	AHNKProjectile* Projectile = SpawnProjectile(SpawnTransform);
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}

AHNKProjectile* UHNKGameplayAbility_FireProjectile::SpawnProjectile(const FTransform& SpawnTransform)
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
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwningActorFromActorInfo();
	SpawnParams.Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	return World->SpawnActor<AHNKProjectile>(ProjectileClass, SpawnTransform, SpawnParams);
}

void UHNKGameplayAbility_FireProjectile::GetSpawnTransform(FTransform& OutSpawnTransform) const
{
	AHNKCharacter* OwnerCharacter = Cast<AHNKCharacter>(GetAvatarActorFromActorInfo());
	if (!OwnerCharacter)
	{
		return;
	}
	
	AController* OwnerController = OwnerCharacter->GetController();
	if (!OwnerController)
	{
		return;
	}
	
	OutSpawnTransform = OwnerCharacter->GetActorTransform();
	OutSpawnTransform.SetLocation(OutSpawnTransform.GetLocation() + OwnerCharacter->GetActorForwardVector() * 200.f);
	OutSpawnTransform.SetRotation(OwnerController->GetControlRotation().Quaternion());
}
