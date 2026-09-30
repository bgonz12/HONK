// Fill out your copyright notice in the Description page of Project Settings.


// HONK Includes
#include "Inventory/HNKInventoryStatics.h"

#include "Inventory/Item/Fragment/HNKItemFragment_Stackable.h"

int32 UHNKInventoryStatics::GetMaxStackCount(TSubclassOf<UHNKItemDefinition> ItemDef)
{
	if (!ensure(IsValid(ItemDef)))
	{
		return -1;
	}
	
	const UHNKItemFragment_Stackable* Fragment = Cast<UHNKItemFragment_Stackable>(UHNKItemDefinition::FindFragmentByClass(ItemDef, UHNKItemFragment_Stackable::StaticClass()));
	if (!IsValid(Fragment))
	{
		return 1;
	}
	
	return Fragment->MaxStacks;
}
