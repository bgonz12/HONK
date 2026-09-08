

// HONK Includes
#include "Gameplay/HNKGameplayStatics.h"

// Engine Includes
#include "GameplayTagContainer.h"

bool UHNKGameplayStatics::TryRequestGameplayTag(const FName& TagName, FGameplayTag& OutTag)
{
	OutTag = FGameplayTag::RequestGameplayTag(TagName, false);
	return OutTag.IsValid();
}

int32 UHNKGameplayStatics::AbilityTagToInputID(const FGameplayTag& AbilityTag)
{
	// Get the FName, extract its FNameEntryId, and convert to raw uint32
	uint32 UnstableInt = AbilityTag.GetTagName().GetComparisonIndex().ToUnstableInt();
	return static_cast<int32>(UnstableInt);
}
