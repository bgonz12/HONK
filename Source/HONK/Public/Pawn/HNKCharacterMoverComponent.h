// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultMovementSet/CharacterMoverComponent.h"
#include "HNKCharacterMoverComponent.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UHNKCharacterMoverComponent : public UCharacterMoverComponent
{
	GENERATED_BODY()

public:
	virtual void OnRegister() override;
};
