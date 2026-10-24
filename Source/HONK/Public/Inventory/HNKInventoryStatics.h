// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/HNKItemDefinition.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HNKInventoryStatics.generated.h"

class UHNKEquipmentComponent;
class UHNKInventoryComponent;

/**
 * 
 */
UCLASS()
class HONK_API UHNKInventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UHNKInventoryComponent* GetInventoryComponentFromActor(const AActor* Actor, bool LookForComponent=true);
	static UHNKEquipmentComponent* GetEquipmentComponentFromActor(const AActor* Actor, bool LookForComponent=true);

	static int32 GetMaxStackCount(TSubclassOf<UHNKItemDefinition> ItemDef);
};
