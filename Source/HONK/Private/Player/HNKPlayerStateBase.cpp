// HONK Includes
#include "Player/HNKPlayerStateBase.h"

// GAS Includes
#include "AbilitySystemComponent.h"

AHNKPlayerStateBase::AHNKPlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(AscReplicationMode);
}

UAbilitySystemComponent* AHNKPlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
