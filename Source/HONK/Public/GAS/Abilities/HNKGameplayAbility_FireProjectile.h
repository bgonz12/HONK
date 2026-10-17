// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "GAS/Abilities/HNKGameplayAbility.h"
#include "HNKGameplayAbility_FireProjectile.generated.h"

class AHNKProjectile;

/**
 * 
 */
UCLASS()
class HONK_API UHNKGameplayAbility_FireProjectile : public UHNKGameplayAbility
{
	GENERATED_BODY()
	
public:
	UHNKGameplayAbility_FireProjectile();
	
protected:
	//~Begin UGameplayAbility
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	//~End UGameplayAbility
	
	AHNKProjectile* SpawnProjectile(const FTransform& SpawnTransform);
	
	void GetSpawnTransform(FTransform& OutSpawnTransform) const;

	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHNKProjectile> ProjectileClass;
};
