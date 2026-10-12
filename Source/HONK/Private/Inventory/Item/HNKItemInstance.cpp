// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Item/HNKItemInstance.h"

// HONK Includes
#include "Inventory/Item/HNKItemDefinition.h"
#include "Inventory/ItemFragment/HNKItemFragment.h"

void UHNKItemInstance::Initialize(TSubclassOf<UHNKItemDefinition> InItemDef)
{
	if (!InItemDef)
	{
		return;
	}
	
	ItemDef = InItemDef;
	
	if (UHNKItemDefinition* ItemDefCDO = ItemDef.GetDefaultObject())
	{
		for (const TObjectPtr<UHNKItemFragment>& ItemFragment : ItemDefCDO->ItemFragments)
		{
			ItemFragment->HandleInstanceCreated(this);
		}
	}
}

float UHNKItemInstance::GetStatValue(FGameplayTag StatTag)
{
	return StatsMap.FindRef(StatTag);
}

void UHNKItemInstance::SetStatValue(FGameplayTag StatTag, float StatValue)
{
	StatsMap.Add(StatTag, StatValue);
}

const UHNKItemFragment* UHNKItemInstance::FindFragmentByClass(const TSubclassOf<UHNKItemFragment> ItemFragmentClass)
{
	if (!ItemFragmentClass)
	{
		return nullptr;
	}
	
	return UHNKItemDefinition::FindFragmentByClass(ItemDef, ItemFragmentClass);
}
