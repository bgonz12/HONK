// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/HNKInventoryStatics.h"

// HONK Includes
#include "Inventory/HNKInventoryComponent.h"
#include "Inventory/HNKInventoryInterface.h"
#include "Inventory/Equipment/HNKEquipmentComponent.h"
#include "Inventory/Equipment/HNKEquipmentComponentInterface.h"
#include "Inventory/ItemFragment/HNKItemFragment_Stackable.h"

UHNKInventoryComponent* UHNKInventoryStatics::GetInventoryComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	if (Actor == nullptr)
	{
		return nullptr;
	}

	if (const IHNKInventoryInterface* InventoryInterface = Cast<IHNKInventoryInterface>(Actor))
	{
		return InventoryInterface->GetInventoryComponent();
	}

	if (LookForComponent)
	{
		// Fall back to a component search to better support BP-only actors
		return Actor->FindComponentByClass<UHNKInventoryComponent>();
	}

	return nullptr;
}

UHNKEquipmentComponent* UHNKInventoryStatics::GetEquipmentComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	if (Actor == nullptr)
	{
		return nullptr;
	}
	
	if (const IHNKEquipmentComponentInterface* ECI = Cast<IHNKEquipmentComponentInterface>(Actor))
	{
		return ECI->GetEquipmentComponent();
	}

	if (LookForComponent)
	{
		// Fall back to a component search to better support BP-only actors
		return Actor->FindComponentByClass<UHNKEquipmentComponent>();
	}

	return nullptr;
}

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
