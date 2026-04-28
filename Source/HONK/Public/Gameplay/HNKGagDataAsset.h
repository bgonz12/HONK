#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

// HONK Includes
#include "HNKGagDataAsset.generated.h"

UCLASS(BlueprintType)
class HONK_API UHNKGagDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName GagName = FName("Gag Name");

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Points = 0.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ComboMultiplier = 0.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ComboTime = 0.f;
};
