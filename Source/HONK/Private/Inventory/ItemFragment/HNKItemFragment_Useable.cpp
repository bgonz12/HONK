// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/ItemFragment/HNKItemFragment_Useable.h"

// HONK Includes
#include "Inventory/ItemAction/HNKItemAction.h"

bool UHNKItemFragment_Useable::Use(AActor* ItemOwner, UHNKItemInstance* ItemInstance) const
{
	bool bAnySuceeded = false;
	
	for (const TObjectPtr<UHNKItemAction>& Action : UseActions)
	{
		if (Action && Action->Execute(ItemOwner, ItemInstance))
		{
			bAnySuceeded = true;
		}
	}
	
	return bAnySuceeded;
}
