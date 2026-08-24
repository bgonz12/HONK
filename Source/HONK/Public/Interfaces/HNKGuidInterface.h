// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HNKGuidInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UHNKGuidInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HONK_API IHNKGuidInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual const FGuid& GetGuid() const = 0;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetGuid(const FGuid& InGuid) {}	
};
