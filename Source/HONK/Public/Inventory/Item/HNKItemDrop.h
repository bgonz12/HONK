// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "GameFramework/Actor.h"

// HONK Includes
#include "Interfaces/HNKGuidInterface.h"
#include "Save/HNKSaveableObjectInterface.h"

#include "HNKItemDrop.generated.h"

UCLASS()
class HONK_API AHNKItemDrop : public AActor, public IHNKGuidInterface
{
	GENERATED_BODY()
	
public:	
	AHNKItemDrop();
	
	//~Begin IHNKGuidInterface
	virtual const FGuid& GetGuid() const override;
	virtual void SetGuid(const FGuid& InGuid) override;
	//~End IHNKGuidInterface
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UHNKItemDefinition* ItemDef;
	
	UPROPERTY(VisibleInstanceOnly)
	FGuid Guid;
};
