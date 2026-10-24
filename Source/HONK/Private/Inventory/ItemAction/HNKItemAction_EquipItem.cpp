// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ItemAction/HNKItemAction_EquipItem.h"

// HONK Includes
#include "Inventory/HNKInventoryStatics.h"
#include "Inventory/Equipment/HNKEquipmentComponent.h"

bool UHNKItemAction_EquipItem::Execute(AActor* ItemOwner, UHNKItemInstance* ItemInstance)
{
	UHNKEquipmentComponent* EquipmentComponent = UHNKInventoryStatics::GetEquipmentComponentFromActor(ItemOwner);
	if (!EquipmentComponent)
	{
		return false;
	}
	
	EquipmentComponent->EquipItem(ItemInstance);
	return true;
}
