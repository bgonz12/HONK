// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "UObject/Interface.h"

// HONK Includes
#include "HNKEquipmentComponentInterface.generated.h"

class UHNKEquipmentComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UHNKEquipmentComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HONK_API IHNKEquipmentComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual UHNKEquipmentComponent* GetEquipmentComponent() const = 0;
};
