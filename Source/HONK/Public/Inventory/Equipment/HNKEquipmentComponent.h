// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "Components/ActorComponent.h"

// HONK Includes
#include "HNKEquipmentComponent.generated.h"

class UHNKEquipmentInstance;
class UHNKItemInstance;
struct FGameplayTagContainer;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HONK_API UHNKEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHNKEquipmentComponent();
	
	void EquipItem(UHNKItemInstance* ItemInstance);
	
	void UnequipItem(UHNKEquipmentInstance* EquipmentInstance);
	
	UFUNCTION(BlueprintPure)
	UHNKEquipmentInstance* FindEquipmentByItemInstance(UHNKItemInstance* ItemInstance);
	
	UFUNCTION(BlueprintPure)
	UHNKEquipmentInstance* FindEquipmentInSlot(const FGameplayTag& SlotTag);
	
protected:
	UPROPERTY()
	TArray<TObjectPtr<UHNKEquipmentInstance>> EquippedItems;
};
