// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

// HONK Includes
#include "GAS/HNKGameplayTags.h"
#include "Save/HNKSaveGame.h"

#include "HNKSaveGame_Player.generated.h"

USTRUCT(BlueprintType)
struct FHNKPlayerCosmeticsData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag HairType = HNKGameplayTags::Cosmetic_Hair_JongleurHatF;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag BodyType = HNKGameplayTags::Cosmetic_Body_Feminine;
};

UCLASS()
class HONK_API UHNKSaveGame_Player : public UHNKSaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHNKPlayerCosmeticsData PlayerCosmetics;
};
