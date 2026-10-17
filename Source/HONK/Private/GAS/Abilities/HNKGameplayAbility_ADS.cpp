// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HNKGameplayAbility_ADS.h"

// Engine Includes
#include "AbilitySystemComponent.h"


UHNKGameplayAbility_ADS::UHNKGameplayAbility_ADS()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UHNKGameplayAbility_ADS::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	
	if (AimingEffect)
	{
		AimingEffectHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, AimingEffect->GetDefaultObject<UGameplayEffect>(), GetAbilityLevel(Handle, ActorInfo));
	}
}

void UHNKGameplayAbility_ADS::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get())
	{
		if (AimingEffectHandle.IsValid())
		{
			ASC->RemoveActiveGameplayEffect(AimingEffectHandle);
			AimingEffectHandle.Invalidate();
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHNKGameplayAbility_ADS::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,	const FGameplayAbilityActivationInfo ActivationInfo)
{	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
