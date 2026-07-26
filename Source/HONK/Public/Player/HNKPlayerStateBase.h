#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"

// HONK Includes
#include "Gameplay/HNKDamageableInterface.h"
#include "HNKPlayerStateBase.generated.h"

class UAbilitySystemComponent;
class UDataTable;

UCLASS()
class HONK_API AHNKPlayerStateBase : public APlayerState, public IAbilitySystemInterface, public IHNKDamageableInterface
{
	GENERATED_BODY()
	
public:
	AHNKPlayerStateBase();

	/** IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
