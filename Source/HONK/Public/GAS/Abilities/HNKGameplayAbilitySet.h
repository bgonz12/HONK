// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "Templates/SubclassOf.h"
#include "UObject/ObjectMacros.h"

// HONK Includes
#include "HNKGameplayAbilitySet.generated.h"

class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FHNKAbilityTagBinding
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Default)
	FGameplayTag AbilityTag;
	
	UPROPERTY(EditAnywhere, Category = Default)
	TSubclassOf<UGameplayAbility> GameplayAbilityClass;
};

UCLASS(BlueprintType)
class HONK_API UHNKGameplayAbilitySet : public UDataAsset
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Category = AbilitySet)
	TArray<FHNKAbilityTagBinding> Abilities;

	UFUNCTION(BlueprintCallable)
	void GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent) const;
	
	UFUNCTION(BlueprintCallable)
	void ClearAbilities(UAbilitySystemComponent* AbilitySystemComponent) const;
};
