// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "Save/HNKSaveGame.h"

#include "HNKSaveGame_Session.generated.h"

class UHNKItemDefinition;

USTRUCT(BlueprintType)
struct FHNKPlacedItemSaveData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UHNKItemDefinition> ItemDef;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform PlacedTransform;
};

UCLASS()
class HONK_API UHNKSaveGame_Session : public UHNKSaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentMoney = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentDay = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FGuid, FHNKPlacedItemSaveData> PlacedItems;
};
