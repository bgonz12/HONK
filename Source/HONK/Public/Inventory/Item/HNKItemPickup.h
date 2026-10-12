// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Item/HNKItemDrop.h"
#include "HNKItemPickup.generated.h"

class UHNKInteractableComponent;
class USceneComponent;

/**
 * 
 */
UCLASS()
class HONK_API AHNKItemPickup : public AHNKItemDrop
{
	GENERATED_BODY()
	
public:
	AHNKItemPickup();
	
	//~Begin UObject
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//~End UObject

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USceneComponent> RootSceneComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UHNKInteractableComponent> InteractableComponent;
};
