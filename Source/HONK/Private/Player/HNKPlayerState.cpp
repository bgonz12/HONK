// HONK Includes
#include "Player/HNKPlayerState.h"
#include "GAS/Attribute/HNKHealthAttributeSet.h"

// Engine Includes
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

AHNKPlayerState::AHNKPlayerState()
{
	SetNetUpdateFrequency(10.f);
}

UAbilitySystemComponent* AHNKPlayerState::GetAbilitySystemComponent() const
{
	if (APawn* MyPawn = GetPawn())
	{
		return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(MyPawn);
	}
	
	return nullptr;
}

void AHNKPlayerState::TryTriggerGag(UHNKGagDataAsset* GagData)
{
	if (!bAllowGags)
	{
		return;
	}
	
	if (HasAuthority())
	{
		TriggerGag(GagData);
	}
	else
	{
		Server_TriggerGag(GagData);
	}
}

void AHNKPlayerState::TriggerGag(UHNKGagDataAsset* GagData)
{
	ScoreGag(GagData);
}

void AHNKPlayerState::Server_TriggerGag_Implementation(UHNKGagDataAsset* GagData)
{
	TriggerGag(GagData);
}
