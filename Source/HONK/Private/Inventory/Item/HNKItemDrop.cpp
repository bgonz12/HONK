// Fill out your copyright notice in the Description page of Project Settings.

// HONK Includes
#include "Inventory/Item/HNKItemDrop.h"

#include "Save/HNKSaveGame_Session.h"

AHNKItemDrop::AHNKItemDrop()
{
	PrimaryActorTick.bCanEverTick = true;

}

const FGuid& AHNKItemDrop::GetGuid() const
{
	return Guid;
}

void AHNKItemDrop::SetGuid(const FGuid& InGuid)
{
	Guid = InGuid;
}

void AHNKItemDrop::SaveObject(USaveGame* SaveGame)
{
	if (!GetGuid().IsValid())
	{
		return;
	}
	
	if (UHNKSaveGame_Session* SessionSave = Cast<UHNKSaveGame_Session>(SaveGame))
	{
		FHNKPlacedItemSaveData& SaveData = SessionSave->PlacedItems.FindOrAdd(GetGuid());
		SaveData.ItemDef = ItemDef;
		SaveData.Transform = PlacedTransform;
	}
}

void AHNKItemDrop::LoadObject(USaveGame* SaveGame)
{
	if (!GetGuid().IsValid())
	{
		return;
	}
	
	if (UHNKSaveGame_Session* SessionSave = Cast<UHNKSaveGame_Session>(SaveGame))
	{
		if (FHNKPlacedItemSaveData* SaveData = SessionSave->PlacedItems.Find(GetGuid()))
		{
			SetPlacedTransform(SaveData->Transform);
			SetActorTransform(SaveData->Transform);
		}
	}
}

void AHNKItemDrop::SetPlacedTransform(const FTransform& InTransform)
{
	PlacedTransform = InTransform;
}

