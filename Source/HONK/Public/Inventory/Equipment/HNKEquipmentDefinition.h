// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "GameplayTagContainer.h"
#include "Inventory/HNKInventoryTypes.h"
#include "UObject/Object.h"

// HONK Includes
#include "HNKEquipmentDefinition.generated.h"

class AHNKEquipmentAttachment;
class UHNKGameplayAbilitySet;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract, Const)
class HONK_API UHNKEquipmentDefinition : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment", meta = (Categories="Equipment.Slot"))
	FGameplayTag SlotTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<UHNKGameplayAbilitySet> AbilitySet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment Attachment")
	TSubclassOf<AHNKEquipmentAttachment> EquipmentAttachmentClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment Attachment")
	FName AttachSocketName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment Attachment")
	FHNKAnimationOverrides AnimationOverrides;
};
