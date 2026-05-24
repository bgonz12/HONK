// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// HONK Includes
#include "HNKItemHologram.generated.h"

UCLASS()
class HONK_API AHNKItemHologram : public AActor
{
	GENERATED_BODY()
	
public:	
	AHNKItemHologram();

protected:
	virtual void BeginPlay() override;
};
