
#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// GAS Includes
#include "AbilitySystemInterface.h"
#include "Gameplay/HNKDamageableInterface.h"

// HONK Includes
#include "HNKCharacterBase.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class UInputComponent;

UCLASS()
class HONK_API AHNKCharacterBase : public ACharacter, public IAbilitySystemInterface, public IHNKDamageableInterface
{
	GENERATED_BODY()

public:
	AHNKCharacterBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	virtual void HandlePlayerStateReady();
	
protected:
	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "HNKCharacterBase|Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
};
