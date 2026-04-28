#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

// GAS Includes
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

// HONK Includes
#include "HNKPlayerStateBase.generated.h"

UCLASS()
class HONK_API AHNKPlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AHNKPlayerStateBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	UAbilitySystemComponent* AbilitySystemComponent;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	EGameplayEffectReplicationMode AscReplicationMode = EGameplayEffectReplicationMode::Mixed;
};
