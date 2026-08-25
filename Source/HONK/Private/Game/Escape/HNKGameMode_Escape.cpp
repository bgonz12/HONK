// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Escape/HNKGameMode_Escape.h"

// HONK Includes
#include "Game/Escape/HNKGameState_Escape.h"
#include "Inventory/Item/HNKItemDefinition.h"
#include "Inventory/Item/HNKItemDrop.h"
#include "Save/HNKSaveGame_Session.h"

void AHNKGameMode_Escape::SaveObject(USaveGame* SaveGame)
{
	if (!SaveGame)
	{
		return;
	}
	
	if (UHNKSaveGame_Session* SessionSave = Cast<UHNKSaveGame_Session>(SaveGame))
	{
		for (TPair<FGuid, FHNKPlacedItemData> PlacedItem : PlacedItems)
		{
			const FGuid& Key = PlacedItem.Key;
			const FHNKPlacedItemData& Value = PlacedItem.Value;
			
			if (!Key.IsValid())
			{
				return;
			}
			
			FHNKPlacedItemSaveData& SaveData = SessionSave->PlacedItems.FindOrAdd(Key);
			SaveData.ItemDef = Value.ItemDef;
			SaveData.PlacedTransform = Value.PlacedTransform;
		}
	}
	
	if (AHNKGameState_Escape* EscapeGameState = Cast<AHNKGameState_Escape>(GameState))
	{
		EscapeGameState->SaveObject(SaveGame);
	}
}

void AHNKGameMode_Escape::LoadObject(USaveGame* SaveGame)
{
	if (!SaveGame)
	{
		return;
	}
	
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	if (UHNKSaveGame_Session* SessionSave = Cast<UHNKSaveGame_Session>(SaveGame))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
		for (TPair<FGuid, FHNKPlacedItemSaveData> PlacedItem : SessionSave->PlacedItems)
		{
			const FGuid& Key = PlacedItem.Key;
			const FHNKPlacedItemSaveData& Data = PlacedItem.Value;
			
			UHNKItemDefinition* ItemDef = Data.ItemDef;
			if (!ItemDef)
			{
				continue;
			}
			
			
			TSubclassOf<AHNKItemDrop> ItemDropClass = ItemDef->ItemDropClass;
			if (!ItemDropClass)
			{
				continue;
			}
			
			if (AHNKItemDrop* ItemDrop = World->SpawnActor<AHNKItemDrop>(ItemDropClass, Data.PlacedTransform, SpawnParams))
			{
				ItemDrop->SetGuid(Key);
				ItemDrop->SetActorTransform(Data.PlacedTransform);
				
				FHNKPlacedItemData& PlacedItemData = PlacedItems.FindOrAdd(Key);
				PlacedItemData.ItemDef = ItemDef;
				PlacedItemData.PlacedTransform = Data.PlacedTransform;
				PlacedItemData.ItemDrop = ItemDrop;
			}
		}
	}
	
	if (AHNKGameState_Escape* EscapeGameState = Cast<AHNKGameState_Escape>(GameState))
	{
		EscapeGameState->LoadObject(SaveGame);
	}
}

void AHNKGameMode_Escape::UpdatePlacedItemTransform(const FGuid& Guid, const FTransform& InTransform)
{
	if (FHNKPlacedItemData* PlacedItemData = PlacedItems.Find(Guid))
	{
		PlacedItemData->PlacedTransform = InTransform;
	}

}
