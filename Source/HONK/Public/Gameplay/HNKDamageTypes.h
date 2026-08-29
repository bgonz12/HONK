#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

// HONK Includes
#include "HNKDamageTypes.Generated.h"

USTRUCT(BlueprintType)
struct FHNKDamagePacket
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UObject> DamageCauser = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UObject> DamageSource = nullptr;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float DamageAmount = 0.f;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FHitResult HitResult;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGameplayTagContainer DamageTags;
};
