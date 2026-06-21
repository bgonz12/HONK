// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

// HONK Includes
#include "HNKDamageCalc.generated.h"

UCLASS()
class HONK_API UHNKDamageCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
		
public:
	UHNKDamageCalc();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
