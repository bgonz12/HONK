
#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

// HONK Includes
#include "Gameplay/HNKDamageableInterface.h"

#include "HNKCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class UInputComponent;

UCLASS()
class HONK_API AHNKCharacter : public ACharacter, public IAbilitySystemInterface, public IHNKDamageableInterface
{
	GENERATED_BODY()

public:
	AHNKCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();

	//~ Begin ACharacter
	virtual void LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride) override;
	virtual void Landed(const FHitResult& Hit) override;
	//~ End ACharacter

	bool GetWasLaunched() const { return bWasLaunched; }
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	virtual void HandlePlayerStateReady();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "HNKCharacterBase|Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	EGameplayEffectReplicationMode AscReplicationMode = EGameplayEffectReplicationMode::Mixed;
	
	UPROPERTY()
	bool bWasLaunched = false;
};
