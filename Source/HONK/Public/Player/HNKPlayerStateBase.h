#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"

// HONK Includes
#include "Gameplay/HNKDamageableInterface.h"
#include "HNKPlayerStateBase.generated.h"

class UAbilitySystemComponent;
class UDataTable;
class UHNKDamageableAttributeSet;

UCLASS()
class HONK_API AHNKPlayerStateBase : public APlayerState, public IAbilitySystemInterface, public IHNKDamageableInterface
{
	GENERATED_BODY()
	
public:
	AHNKPlayerStateBase();
	
	void InitAbilitySystem();

	/** IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	/** IHNKDamageableInterface */
	virtual void DamageTaken(FHNKDamagePacket& DamagePacket) override;
	virtual float GetHealth() const override;
	virtual float GetMaxHealth() const override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	const UHNKDamageableAttributeSet* DamageableAttributeSet;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	EGameplayEffectReplicationMode AscReplicationMode = EGameplayEffectReplicationMode::Mixed;
};
