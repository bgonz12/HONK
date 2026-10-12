// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ItemAction/HNKItemAction_EquipItem.h"

// HONK Includes
#include "Inventory/Equipment/HNKEquipmentComponent.h"
#include "Inventory/Equipment/HNKEquipmentComponentInterface.h"

bool UHNKItemAction_EquipItem::Execute(AActor* ItemOwner, UHNKItemInstance* ItemInstance)
{
	IHNKEquipmentComponentInterface* EquipmentComponentInterface = Cast<IHNKEquipmentComponentInterface>(ItemOwner);
	if (!EquipmentComponentInterface)
	{
		return false;
	}
	
	UHNKEquipmentComponent* EquipmentComponent = EquipmentComponentInterface->GetEquipmentComponent();
	if (!EquipmentComponent)
	{
		return false;
	}
	
	EquipmentComponent->EquipItem(ItemInstance);
	return true;
}
