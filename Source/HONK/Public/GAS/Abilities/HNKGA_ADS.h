// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engiine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "GAS/Abilities/HNKGameplayAbility.h"
#include "HNKGA_ADS.generated.h"

class UGameplayEffect;

UCLASS()
class HONK_API UHNKGA_ADS : public UHNKGameplayAbility
{
	GENERATED_BODY()
	
public:
	UHNKGA_ADS();
	
protected:
	//~ Begin UGameplayAbility
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	//~ End UGameplayAbility

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
	TSubclassOf<UGameplayEffect> AimingEffect;
	
	FActiveGameplayEffectHandle AimingEffectHandle;
};
