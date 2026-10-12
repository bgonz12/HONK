// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "GameplayTagContainer.h"
#include "UObject/Object.h"

// HONK Includes
#include "HNKItemInstance.generated.h"

class UHNKItemDefinition;

/**
 * 
 */
UCLASS()
class HONK_API UHNKItemInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Item Initialization")
	void Initialize(TSubclassOf<UHNKItemDefinition> InItemDef);
	
	UFUNCTION(BlueprintPure, Category = "Item Stats")
	float GetStatValue(FGameplayTag StatTag);
	
	UFUNCTION(BlueprintCallable, Category = "Item Stats")
	void SetStatValue(FGameplayTag StatTag, float StatValue);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DeterminesOutputType = "ItemFragmentClass"))
	const UHNKItemFragment* FindFragmentByClass(const TSubclassOf<UHNKItemFragment> ItemFragmentClass);
	
public:
	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UHNKItemDefinition> ItemDef;
	
	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag, float> StatsMap;
};
