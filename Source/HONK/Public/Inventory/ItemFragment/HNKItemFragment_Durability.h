// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HNKItemFragment.h"
#include "HNKItemFragment_Durability.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UHNKItemFragment_Durability : public UHNKItemFragment
{
	GENERATED_BODY()
	
public:
	//~Begin UHNKItemFragment
	virtual void HandleInstanceCreated(UHNKItemInstance* ItemInstance) override;
	//~End UHNKItemFragment
	
	void ReduceDurability(UHNKItemInstance* ItemInstance, int32 Amount);
	
	bool HasAnyRemainingDurability(UHNKItemInstance* ItemInstance);
	
	int32 GetMaxDurability();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options", meta = (UIMin = "1", UIMax = "999", ClampMin = "1"))
	int32 MaxDurability = 1;
};
