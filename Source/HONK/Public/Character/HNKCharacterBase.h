
#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// GAS Includes
#include "AbilitySystemInterface.h"

// HONK Includes
#include "HNKCharacterBase.generated.h"

UCLASS()
class HONK_API AHNKCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHNKCharacterBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
};
