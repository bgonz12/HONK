// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

// HONK Inlcudes
#include "HNKHealthAttributeSet.generated.h"

struct FHNKDamagePacket;

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class HONK_API UHNKHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UHNKHealthAttributeSet();
	
	//~Begin UObject
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~End UObject
	
	//~Begin UAttributeSet
	virtual bool ShouldInitProperty(bool FirstInit, FProperty* PropertyToInit) const override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	//~End UAttributeSet
	
	static FHNKDamagePacket MakeDamagePacketFromEffectContext(const FGameplayEffectContextHandle& EffectContextHandle, const FGameplayEffectSpec& EffectSpec, const float Damage);
	
protected:
	void TryApplyDamage(const FHNKDamagePacket& DamagePacket);
	
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UFUNCTION()
	virtual void OnRep_DamageMod(const FGameplayAttributeData& OldDamageMod);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UHNKHealthAttributeSet, Health)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UHNKHealthAttributeSet, MaxHealth)
	
	// Damage is a meta attribute used by the DamageExecution to calculate final damage, which then turns into -Health
	// Temporary value that only exists on the Server. Not replicated.
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UHNKHealthAttributeSet, Damage)
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_DamageMod)
	FGameplayAttributeData DamageMod;
	ATTRIBUTE_ACCESSORS(UHNKHealthAttributeSet, DamageMod)

};
