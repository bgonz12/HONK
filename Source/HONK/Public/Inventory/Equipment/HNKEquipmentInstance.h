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
	//~Begin UObject
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override;
	//~End UObject
	
	void Initialize(UHNKItemInstance* ItemInstance, ACharacter* Character);
	
	void HandleEquipItem(ACharacter* Character);
	
	void HandleUnequipItem(ACharacter* Character);
	
	UPROPERTY(Replicated, BlueprintReadOnly)
	TSubclassOf<UHNKEquipmentDefinition> EquipmentDef;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UHNKItemInstance> SourceItemInstance;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Transient)
	TObjectPtr<AHNKEquipmentAttachment> AttachmentActor;
};
