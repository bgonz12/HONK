// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HNKGameplayAbility.h"

UHNKGameplayAbility::UHNKGameplayAbility()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}
