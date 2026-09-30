// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "HNKItemFragment.h"
#include "HNKItemFragment_WorldRepresentation.generated.h"

class AHNKItemDrop;

UCLASS()
class HONK_API UHNKItemFragment_WorldRepresentation : public UHNKItemFragment
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMesh> ItemMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Drop")
	TSubclassOf<AHNKItemDrop> ItemDropClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Drop")
	bool bCanBeDropped = true;
};
