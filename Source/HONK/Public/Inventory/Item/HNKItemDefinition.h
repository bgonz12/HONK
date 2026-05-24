// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "Engine/DataAsset.h"
#include "HNKItemDefinition.generated.h"

UCLASS(BlueprintType)
class HONK_API UHNKItemDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName ItemName;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* ItemIcon;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class AHNKItemDrop> ItemDropClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class AHNKItemConstruct> ItemConstructClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class AHNKItemHologram> ItemHologramClass;
};
