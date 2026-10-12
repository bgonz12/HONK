// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "GameFramework/Actor.h"

// HONK Includes
#include "HNKEquipmentAttachment.generated.h"

UCLASS(Abstract)
class HONK_API AHNKEquipmentAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	AHNKEquipmentAttachment();
};
