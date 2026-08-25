// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "HNKInventoryTypes.generated.h"

class UHNKItemDefinition;
class AHNKItemDrop;

USTRUCT(BlueprintType)
struct FHNKItemShopData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHNKItemDefinition* ItemDef;
};

USTRUCT(BlueprintType)
struct FHNKPlacedItemData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UHNKItemDefinition> ItemDef;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform PlacedTransform;
	
	UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<AHNKItemDrop> ItemDrop;
};
