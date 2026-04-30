// HONK Includes
#include "Player/HNKPlayerStateBase.h"

// GAS Includes
#include "AbilitySystemComponent.h"

AHNKPlayerStateBase::AHNKPlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(AscReplicationMode);
	
	// Need to increase the NetUpdateFrequency because the AbilitySystemComponent is stored on this actor
	NetUpdateFrequency = 30.f;
}

UAbilitySystemComponent* AHNKPlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
