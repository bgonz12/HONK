// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "UObject/Object.h"

// HONK Includes
#include "HNKItemAction.generated.h"

class UHNKItemInstance;

UCLASS(Blueprintable, BlueprintType, Abstract, DefaultToInstanced, EditInlineNew)
class HONK_API UHNKItemAction : public UObject
{
	GENERATED_BODY()
	
public:
	virtual bool Execute(AActor* ItemOwner, UHNKItemInstance* ItemInstance);
};
