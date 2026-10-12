// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "HNKItemFragment.h"
#include "HNKItemFragment_Equippable.generated.h"

class UHNKEquipmentDefinition;

/**
 * 
 */
UCLASS()
class HONK_API UHNKItemFragment_Equippable : public UHNKItemFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TSubclassOf<UHNKEquipmentDefinition> EquipmentDef;
};
