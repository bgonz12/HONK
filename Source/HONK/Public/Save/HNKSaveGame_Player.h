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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.Body"))
	FGameplayTag BodyType = HNKGameplayTags::Cosmetic_Body_Feminine;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.Hair"))
	FGameplayTag HairType = HNKGameplayTags::Cosmetic_Hair_JongleurHatF;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.HairColor"))
	FGameplayTag HairColor = HNKGameplayTags::Cosmetic_HairColor_Blue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.Eyes"))
	FGameplayTag EyesType = HNKGameplayTags::Cosmetic_Eyes_1F;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.EyeColor"))
	FGameplayTag EyeColor = HNKGameplayTags::Cosmetic_EyeColor_Pink1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.Mouth"))
	FGameplayTag MouthType = HNKGameplayTags::Cosmetic_Mouth_1F;
};

UCLASS()
class HONK_API UHNKSaveGame_Player : public UHNKSaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHNKPlayerCosmeticsData PlayerCosmetics;
};
