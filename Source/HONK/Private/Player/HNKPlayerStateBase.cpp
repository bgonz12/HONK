// HONK Includes
#include "Player/HNKPlayerStateBase.h"
#include "GAS/Attribute/HNKHealthAttributeSet.h"

// Engine Includes
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

AHNKPlayerStateBase::AHNKPlayerStateBase()
{
	SetNetUpdateFrequency(10.f);
}

UAbilitySystemComponent* AHNKPlayerStateBase::GetAbilitySystemComponent() const
{
	if (APawn* MyPawn = GetPawn())
	{
		return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(MyPawn);
	}
	
	return nullptr;
}
