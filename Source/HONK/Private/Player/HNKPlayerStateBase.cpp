// HONK Includes
#include "Player/HNKPlayerStateBase.h"
#include "GAS/Attribute/HNKDamageableAttributeSet.h"

// Engine Includes
#include "AbilitySystemComponent.h"

AHNKPlayerStateBase::AHNKPlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(AscReplicationMode);

	// Setup attribute sets
	DamageableAttributeSet = CreateDefaultSubobject<UHNKDamageableAttributeSet>(TEXT("DamageableAttributeSet"));
	
	// Need to increase the NetUpdateFrequency because the AbilitySystemComponent is stored on this actor
	SetNetUpdateFrequency(30.f);
}

void AHNKPlayerStateBase::InitAbilitySystem()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (IsValid(ASC))
	{
		ASC->InitAbilityActorInfo(this, GetPawn());
		DamageableAttributeSet = ASC->GetSet<UHNKDamageableAttributeSet>();
	}
}

UAbilitySystemComponent* AHNKPlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AHNKPlayerStateBase::DamageTaken(FHNKDamagePacket& DamagePacket)
{
}

float AHNKPlayerStateBase::GetHealth() const
{
	if (!IsValid(DamageableAttributeSet))
	{
		return -1.f;
	}
	
	return DamageableAttributeSet->GetHealth();
}

float AHNKPlayerStateBase::GetMaxHealth() const
{
	if (!IsValid(DamageableAttributeSet))
	{
		return -1.f;
	}
	
	return DamageableAttributeSet->GetMaxHealth();
}
