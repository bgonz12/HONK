// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "HNKInventoryTypes.generated.h"

class UHNKItemDefinition;
class UHNKItemInstance;
class AHNKItemDrop;

USTRUCT(BlueprintType)
struct FHNKItemDefinitionStack
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UHNKItemDefinition> ItemDef;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = "1", UIMax = "999", ClampMin = "1"))
	int32 Count = 1;
};

USTRUCT(BlueprintType)
struct FHNKItemInstanceStack
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UHNKItemInstance> ItemInstance;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = "1", UIMax = "999", ClampMin = "1"))
	int32 Count = 1;
};

USTRUCT(BlueprintType)
struct FHNKItemShopData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UHNKItemDefinition> ItemDef;
};

USTRUCT(BlueprintType)
struct FHNKPlacedItemData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UHNKItemDefinition> ItemDef;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform PlacedTransform;
	
	UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<AHNKItemDrop> ItemDrop;
};

USTRUCT(BlueprintType)
struct FHNKAnimationOverrides
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAnimSequence> IdleAnim;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBlendSpace> WalkRunBlendspace;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBlendSpace> JumpingBlendspace;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBlendSpace> FallingBlendspace;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bMirrorUpperBodyWhenJumping = false;
	
	bool IsValid() const
	{
		return IdleAnim && WalkRunBlendspace && JumpingBlendspace && FallingBlendspace;
	}
};
