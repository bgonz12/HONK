// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "HNKItemFragment.h"
#include "HNKItemFragment_Stackable.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UHNKItemFragment_Stackable : public UHNKItemFragment
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options", meta = (UIMin = "1", UIMax = "999", ClampMin = "1"))
	int32 MaxStacks = 1;
};
