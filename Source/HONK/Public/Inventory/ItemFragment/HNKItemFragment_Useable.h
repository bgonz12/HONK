// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "Inventory/ItemFragment/HNKItemFragment.h"
#include "HNKItemFragment_Useable.generated.h"

class UHNKItemAction;
class UHNKItemInstance;

UCLASS()
class HONK_API UHNKItemFragment_Useable : public UHNKItemFragment
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool Use(AActor* ItemOwner, UHNKItemInstance* ItemInstance) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	bool bUseOnPickup = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	bool bConsumeOnUse = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	TArray<TObjectPtr<UHNKItemAction>> UseActions;
};
