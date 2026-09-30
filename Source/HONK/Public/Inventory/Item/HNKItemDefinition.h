// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "HNKItemDefinition.generated.h"

class AHNKItemDrop;
class UHNKItemFragment;
class AHNKItemHologram;

UCLASS(Blueprintable, BlueprintType, Abstract, Const)
class HONK_API UHNKItemDefinition : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Display")
	FText ItemName;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Display")
	FText ItemDescription;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Display")
	UTexture2D* ItemIcon;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 BaseCost = 0;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<AHNKItemDrop> ItemDropClass;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<AHNKItemHologram> ItemHologramClass;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced, Category = "Fragments Array")
	TArray<TObjectPtr<UHNKItemFragment>> ItemFragments;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DeterminesOutputType = "ItemFragmentClass"))
	static const UHNKItemFragment* FindFragmentByClass(const TSubclassOf<UHNKItemDefinition> ItemDef, const TSubclassOf<UHNKItemFragment> ItemFragmentClass);
};
