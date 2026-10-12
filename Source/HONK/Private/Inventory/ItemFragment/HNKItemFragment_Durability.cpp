// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/ItemFragment/HNKItemFragment_Durability.h"

// HONK Includes
#include "GAS/HNKGameplayTags.h"
#include "Inventory/Item/HNKItemInstance.h"

void UHNKItemFragment_Durability::HandleInstanceCreated(UHNKItemInstance* ItemInstance)
{
	ItemInstance->SetStatValue(HNKGameplayTags::Item_Stat_Durability, GetMaxDurability());
}

void UHNKItemFragment_Durability::ReduceDurability(UHNKItemInstance* ItemInstance, int32 Amount)
{
	const int32 OldDurability = ItemInstance->GetStatValue(HNKGameplayTags::Item_Stat_Durability);
	const int32 NewDurability = FMath::Clamp(OldDurability - Amount, 0, GetMaxDurability());
	
	ItemInstance->SetStatValue(HNKGameplayTags::Item_Stat_Durability, NewDurability);
}

bool UHNKItemFragment_Durability::HasAnyRemainingDurability(UHNKItemInstance* ItemInstance)
{
	if (!ItemInstance)
	{
		return false;
	}
	
	return ItemInstance->GetStatValue(HNKGameplayTags::Item_Stat_Durability) > 0.f;
}

int32 UHNKItemFragment_Durability::GetMaxDurability()
{
	return MaxDurability;
}
