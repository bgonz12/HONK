#pragma once

// Engine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "HNKDamageTypes.Generated.h"

USTRUCT(BlueprintType)
struct FHNKDamagePacket
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UObject> DamagerObject = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UObject> DamagedObject = nullptr;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float DamageAmount = 0.f;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FHitResult HitResult;
};
