// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "NativeGameplayTags.h"

namespace HNKGameplayTags
{
	// Ability State Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_State_Aiming);
	
	// Cosmetic Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cosmetic_Body_Feminine);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cosmetic_Body_Masculine);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cosmetic_Hair_JongleurHatF);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cosmetic_Hair_Pompadour);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cosmetic_HairColor_Blue);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cosmetic_Eyes_1F);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cosmetic_EyeColor_Pink1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cosmetic_Mouth_1F);

	// Cue Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_PlaySound);
	
	// Equipment Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment_Slot_MainHand);

	// Item Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Stat_Durability);
}
