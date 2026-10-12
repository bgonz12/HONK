// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "HNKItemAction.h"
#include "HNKItemAction_EquipItem.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UHNKItemAction_EquipItem : public UHNKItemAction
{
	GENERATED_BODY()
	
public:
	virtual bool Execute(AActor* ItemOwner, UHNKItemInstance* ItemInstance) override;
};
