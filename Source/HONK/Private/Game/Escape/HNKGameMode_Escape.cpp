// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Escape/HNKGameMode_Escape.h"

// HONK Includes
#include "Game/Escape/HNKGameState_Escape.h"
#include "Inventory/Item/HNKItemDefinition.h"
#include "Inventory/Item/HNKItemDrop.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Save/HNKSaveGame_Session.h"

void AHNKGameMode_Escape::SaveObject(USaveGame* SaveGame)
{
	if (!SaveGame)
	{
		return;
	}
	
	for (AHNKItemDrop* PlacedItem : PlacedItems)
	{
		PlacedItem->SaveObject(SaveGame);
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
			
			if (AHNKItemDrop* ItemDrop = World->SpawnActor<AHNKItemDrop>(ItemDropClass, Data.Transform, SpawnParams))
			{
				ItemDrop->SetGuid(Key);
				ItemDrop->LoadObject(SaveGame);
				PlacedItems.Add(ItemDrop);
			}
		}
	}
	
	if (AHNKGameState_Escape* EscapeGameState = Cast<AHNKGameState_Escape>(GameState))
	{
		EscapeGameState->LoadObject(SaveGame);
	}
}
