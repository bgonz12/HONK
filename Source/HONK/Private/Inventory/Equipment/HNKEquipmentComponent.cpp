// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Equipment/HNKEquipmentComponent.h"

// HONK Includes
#include "Inventory/Equipment/HNKEquipmentDefinition.h"
#include "Inventory/Equipment/HNKEquipmentInstance.h"
#include "Inventory/Item/HNKItemInstance.h"
#include "Inventory/ItemFragment/HNKItemFragment_Equippable.h"

// Engine Includes
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "Net/UnrealNetwork.h"

UHNKEquipmentComponent::UHNKEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
}

void UHNKEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UHNKEquipmentComponent, EquippedItems);
}

void UHNKEquipmentComponent::EquipItem(UHNKItemInstance* ItemInstance)
{
	if (!ItemInstance)
	{
		return;
	}
	
	// Check if item is already equipped
	if (UHNKEquipmentInstance* EquippedItem = FindEquipmentByItemInstance(ItemInstance))
	{
		UnequipItem(EquippedItem);
		return;
	}
	
	// Check if item slot is already occupied
	const UHNKItemFragment_Equippable* EquippableFragment = Cast<UHNKItemFragment_Equippable>(ItemInstance->FindFragmentByClass(UHNKItemFragment_Equippable::StaticClass()));
	if (!EquippableFragment)
	{
		return;
	}

	const UHNKEquipmentDefinition* EquipmentDefCDO = EquippableFragment->EquipmentDef.GetDefaultObject();
	if (!EquipmentDefCDO)
	{
		return;
	}

	if (UHNKEquipmentInstance* EquippedItem = FindEquipmentInSlot(EquipmentDefCDO->SlotTag))
	{
		UnequipItem(EquippedItem);
	}
	
	ACharacter* OwnerCharacter = GetOwner<ACharacter>();
	if (!OwnerCharacter)
	{
		return;
	}
	
	UHNKEquipmentInstance* EquipmentInstance = NewObject<UHNKEquipmentInstance>(this);
	if (!ensure(EquipmentInstance))
	{
		return;
	}
	
	AddReplicatedSubObject(EquipmentInstance);
	
	EquipmentInstance->Initialize(ItemInstance, OwnerCharacter);
	EquippedItems.AddUnique(EquipmentInstance);
}

void UHNKEquipmentComponent::UnequipItem(UHNKEquipmentInstance* EquipmentInstance)
{
	if (!EquipmentInstance)
	{
		return;
	}
	
	if (ACharacter* OwnerCharacter = GetOwner<ACharacter>())
	{
		EquipmentInstance->HandleUnequipItem(OwnerCharacter);
		EquippedItems.Remove(EquipmentInstance);
	}
}

UHNKEquipmentInstance* UHNKEquipmentComponent::FindEquipmentByItemInstance(UHNKItemInstance* ItemInstance)
{
	for (UHNKEquipmentInstance* EquippedItem : EquippedItems)
	{
		if (EquippedItem->SourceItemInstance == ItemInstance)
		{
			return EquippedItem;
		}
	}
	
	return nullptr;
}

UHNKEquipmentInstance* UHNKEquipmentComponent::FindEquipmentInSlot(const FGameplayTag& SlotTag)
{
	for (UHNKEquipmentInstance* EquippedItem : EquippedItems)
	{
		if (!EquippedItem)
		{
			continue;
		}
		
		if (const UHNKEquipmentDefinition* EquipmentDefCDO = EquippedItem->EquipmentDef.GetDefaultObject())
		{
			if (EquipmentDefCDO->SlotTag == SlotTag)
			{
				return EquippedItem;
			}
		}
	}
	
	return nullptr;
}

