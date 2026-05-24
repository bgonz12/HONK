// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// HONK Includes
#include "HNKItemConstruct.generated.h"

UCLASS()
class HONK_API AHNKItemConstruct : public AActor
{
	GENERATED_BODY()
	
public:	
	AHNKItemConstruct();

protected:
	virtual void BeginPlay() override;
};
