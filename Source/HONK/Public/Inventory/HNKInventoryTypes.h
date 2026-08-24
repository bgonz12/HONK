// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "HNKInventoryTypes.generated.h"

USTRUCT(BlueprintType)
struct FHNKItemShopData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UHNKItemDefinition* ItemDef;
};
