// Fill out your copyright notice in the Description page of Project Settings.

// HONK Includes
#include "GAS/Attribute/HNKDamageableAttributeSet.h"

// Engine Includes
#include "Net/UnrealNetwork.h"

void UHNKDamageableAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHNKDamageableAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHNKDamageableAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UHNKDamageableAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHNKDamageableAttributeSet, Health, OldHealth);
}

void UHNKDamageableAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHNKDamageableAttributeSet, MaxHealth, OldMaxHealth);
}
