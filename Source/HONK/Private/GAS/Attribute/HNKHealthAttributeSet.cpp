// Fill out your copyright notice in the Description page of Project Settings.

// HONK Includes
#include "GAS/Attribute/HNKHealthAttributeSet.h"

// Engine Includes
#include "GameplayEffectExtension.h"
#include "Gameplay/HNKDamageableInterface.h"
#include "Gameplay/HNKDamageTypes.h"
#include "Net/UnrealNetwork.h"

UHNKHealthAttributeSet::UHNKHealthAttributeSet()
{
	InitMaxHealth(100.f);
	InitHealth(100.f);
	InitDamageMod(1.f);
}

void UHNKHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHNKHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHNKHealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHNKHealthAttributeSet, DamageMod, COND_None, REPNOTIFY_Always);
}

bool UHNKHealthAttributeSet::ShouldInitProperty(bool FirstInit, FProperty* PropertyToInit) const
{
	if (PropertyToInit == GetDamageAttribute().GetUProperty())
	{
		return false;
	}
	
	return true;
}

bool UHNKHealthAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		Data.EvaluatedData.Magnitude *= GetDamageMod();

		if (AActor* OwnerActorPtr = GetOwningActor())
		{
			IHNKDamageableInterface* DamageableInterface = Cast<IHNKDamageableInterface>(OwnerActorPtr);
			if (!DamageableInterface)
			{
				UE_LOG(LogTemp, Error, TEXT("*** %s - doesn't implement the HNKDamagableInterface, but is attempting to modify damage"), *OwnerActorPtr->GetName());
				return true;
			}

			FHNKDamagePacket DamagePacket = MakeDamagePacketFromEffectContext(Data.EffectSpec.GetContext(), Data.EffectSpec, Data.EvaluatedData.Magnitude);
			DamageableInterface->ModifyDamage(DamagePacket);
			
			Data.EvaluatedData.Magnitude = DamagePacket.DamageAmount;
		}
	}
	
	return true;
}

void UHNKHealthAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (GetDamage() != 0.0f)
		{
			FHNKDamagePacket AttemptedDamage = MakeDamagePacketFromEffectContext(Data.EffectSpec.GetContext(), Data.EffectSpec, GetDamage());
			TryApplyDamage(AttemptedDamage);
			SetDamage(0.0f);
		}
	}
}

void UHNKHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == GetMaxHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}

FHNKDamagePacket UHNKHealthAttributeSet::MakeDamagePacketFromEffectContext(const FGameplayEffectContextHandle& EffectContextHandle, const FGameplayEffectSpec& EffectSpec, const float Damage)
{
	FHNKDamagePacket DamagePacket;
	DamagePacket.DamageAmount = Damage;
	DamagePacket.DamageCauser = EffectContextHandle.GetEffectCauser();
	DamagePacket.DamageSource = Cast<AActor>(EffectContextHandle.GetSourceObject());
	
	FGameplayTagContainer ActorTagContainer;
	EffectContextHandle.GetOwnedGameplayTags(ActorTagContainer, DamagePacket.DamageTags);
	EffectSpec.GetAllAssetTags(DamagePacket.DamageTags);
	
	if (const FHitResult* EffectHitResult = EffectContextHandle.GetHitResult())
	{
		DamagePacket.HitResult = *EffectHitResult;
	}
	
	return DamagePacket;
}

void UHNKHealthAttributeSet::TryApplyDamage(const FHNKDamagePacket& DamagePacket)
{
	if (AActor* OwningActor = GetOwningActor())
	{
		IHNKDamageableInterface* DamageableInterface = Cast<IHNKDamageableInterface>(OwningActor);
		if (!DamageableInterface)
		{
			UE_LOG(LogTemp, Error, TEXT("*** %s - doesn't implement the HNKDamagableInterface, but is still having damage applied"), *OwningActor->GetName());
			return;
		}
			
		// Checks is no damage was used on armor or if roll over is allowed
		if (GetHealth() > 0)
		{
			SetHealth(FMath::Clamp(GetHealth() - DamagePacket.DamageAmount, 0.0f, GetMaxHealth()));
			
			DamageableInterface->DamageTaken(DamagePacket);
		
			if (IHNKDamageableInterface* DamagerInterface = Cast<IHNKDamageableInterface>(DamagePacket.DamageCauser))
			{
				DamagerInterface->DamageDealt(DamagePacket);
			}
			
			if (GetHealth() == 0)
			{
				DamageableInterface->Died(DamagePacket);
			}
		}
	}
}

void UHNKHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHNKHealthAttributeSet, Health, OldHealth);
}

void UHNKHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHNKHealthAttributeSet, MaxHealth, OldMaxHealth);
}

void UHNKHealthAttributeSet::OnRep_DamageMod(const FGameplayAttributeData& OldDamageMod)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHNKHealthAttributeSet, DamageMod, OldDamageMod);
}
