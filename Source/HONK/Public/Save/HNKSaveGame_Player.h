// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

// HONK Includes
#include "Save/HNKSaveGame.h"

#include "HNKSaveGame_Player.generated.h"

USTRUCT(BlueprintType)
struct FHNKPlayerCosmeticsData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.Body"))
	FGameplayTag BodyType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.Hair"))
	FGameplayTag HairType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.HairColor"))
	FGameplayTag HairColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.Eyes"))
	FGameplayTag EyesType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.EyeColor"))
	FGameplayTag EyeColor;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories="Cosmetic.Mouth"))
	FGameplayTag MouthType;
	
	bool IsValid() const
	{
		return BodyType.IsValid() 
			&& HairType.IsValid() 
			&& HairColor.IsValid() 
			&& EyesType.IsValid()
			&& EyeColor.IsValid() 
			&& MouthType.IsValid();
	}
};

UCLASS()
class HONK_API UHNKSaveGame_Player : public UHNKSaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHNKPlayerCosmeticsData PlayerCosmetics;
};
