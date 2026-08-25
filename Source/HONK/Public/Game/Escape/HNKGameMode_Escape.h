// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "Game/HNKGameMode.h"
#include "Inventory/HNKInventoryTypes.h"
#include "Save/HNKSaveableObjectInterface.h"

#include "HNKGameMode_Escape.generated.h"

class AHNKItemDrop;
class USaveGame;

UCLASS()
class HONK_API AHNKGameMode_Escape : public AHNKGameMode, public IHNKSaveableObjectInterface
{
	GENERATED_BODY()
	
public:
	//~Begin IHNKSaveableObjectInterface
	virtual void SaveObject(USaveGame* SaveGame) override;
	virtual void LoadObject(USaveGame* SaveGame) override;
	//~End IHNKSaveableObjectInterface
	
	UFUNCTION(BlueprintCallable)
	void UpdatePlacedItemTransform(const FGuid& Guid, const FTransform& InTransform);
	
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FGuid, FHNKPlacedItemData> PlacedItems;
};
