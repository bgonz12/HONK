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
