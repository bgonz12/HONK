// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "Engine/DataAsset.h"
#include "HNKItemDefinition.generated.h"

class AHNKItemDrop;
class AHNKItemHologram;

UCLASS(BlueprintType)
class HONK_API UHNKItemDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName ItemName;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* ItemIcon;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BaseCost = 0;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<AHNKItemDrop> ItemDropClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<AHNKItemHologram> ItemHologramClass;
};
