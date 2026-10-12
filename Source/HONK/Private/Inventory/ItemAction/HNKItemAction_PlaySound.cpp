// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ItemAction/HNKItemAction_PlaySound.h"

// HONK Includes
#include "GAS/HNKGameplayTags.h"

// Engine Includes
#include "GameplayCueFunctionLibrary.h"


bool UHNKItemAction_PlaySound::Execute(AActor* ItemOwner, UHNKItemInstance* ItemInstance)
{
	FGameplayCueParameters Parameters;
	Parameters.SourceObject = Sound;
	
	UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(ItemOwner, HNKGameplayTags::GameplayCue_PlaySound, Parameters);
	
	return true;
}
