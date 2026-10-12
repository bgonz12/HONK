// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "UObject/Object.h"

// HONK Includes
#include "HNKEquipmentInstance.generated.h"

class AHNKEquipmentAttachment;
class UHNKItemInstance;
class UHNKEquipmentDefinition;

UCLASS(BlueprintType)
class HONK_API UHNKEquipmentInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UHNKEquipmentDefinition> EquipmentDef;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UHNKItemInstance> SourceItemInstance;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AHNKEquipmentAttachment> EquipmentAttachmentActor;
	
	void Initialize(UHNKItemInstance* ItemInstance, ACharacter* Character);
	
	void HandleEquipItem(ACharacter* Character);
	
	void HandleUnequipItem(ACharacter* Character);
};
