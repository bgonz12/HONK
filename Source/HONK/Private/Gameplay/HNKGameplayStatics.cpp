

// HONK Includes
#include "Gameplay/HNKGameplayStatics.h"

// Engine Includes
#include "GameplayTagContainer.h"

bool UHNKGameplayStatics::TryRequestGameplayTag(const FName& TagName, FGameplayTag& OutTag)
{
	OutTag = FGameplayTag::RequestGameplayTag(TagName, false);
	return OutTag.IsValid();
}
