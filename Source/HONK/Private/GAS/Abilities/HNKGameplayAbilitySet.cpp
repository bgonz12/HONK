// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Abilities/HNKGameplayAbilitySet.h"

// HONK Includes
#include "Gameplay/HNKGameplayStatics.h"

// Engine Includes
#include "AbilitySystemComponent.h"

void UHNKGameplayAbilitySet::GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent) const
{
	for (const FHNKAbilityTagBinding& BindInfo : Abilities)
	{
		if (BindInfo.GameplayAbilityClass)
		{
			const int32 InputID = UHNKGameplayStatics::AbilityTagToInputID(BindInfo.AbilityTag);
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(BindInfo.GameplayAbilityClass, 1, InputID));
		}
	}
}

void UHNKGameplayAbilitySet::ClearAbilities(UAbilitySystemComponent* AbilitySystemComponent) const
{
	for (const FHNKAbilityTagBinding& BindInfo : Abilities)
	{
		if (BindInfo.GameplayAbilityClass)
		{
			const int32 InputID = UHNKGameplayStatics::AbilityTagToInputID(BindInfo.AbilityTag);
			AbilitySystemComponent->ClearAllAbilitiesWithInputID(InputID);
		}
	}
}
