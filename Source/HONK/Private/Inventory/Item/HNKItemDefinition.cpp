// Fill out your copyright notice in the Description page of Project Settings.

// HONK Includes
#include "Inventory/Item/HNKItemDefinition.h"

#include "Inventory/Item/Fragment/HNKItemFragment.h"

const UHNKItemFragment* UHNKItemDefinition::FindFragmentByClass(const TSubclassOf<UHNKItemDefinition> ItemDef, const TSubclassOf<UHNKItemFragment> ItemFragmentClass)
{
	if (!ItemDef || !ItemFragmentClass)
	{
		return nullptr;
	}
	
	UHNKItemDefinition* ItemDefCDO = ItemDef.GetDefaultObject();
	if (!ItemDefCDO)
	{
		return nullptr;
	}
	
	for (const TObjectPtr<UHNKItemFragment>& ItemFragment : ItemDefCDO->ItemFragments)
	{
		if (ItemFragment->IsA(ItemFragmentClass))
		{
			return ItemFragment;
		}
	}
	
	return nullptr;
}
