// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// HONK Includes
#include "HNKItemDrop.generated.h"

UCLASS()
class HONK_API AHNKItemDrop : public AActor
{
	GENERATED_BODY()
	
public:	
	AHNKItemDrop();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
