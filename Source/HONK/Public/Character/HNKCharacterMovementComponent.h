// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HNKCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UHNKCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
	
public:
	//~ Begin UActorComponent
	virtual float GetGravityZ() const override;
	//~ End UActorComponent
	
	bool ShouldApplyJumpGravity() const;
	
protected:
	/** Modifier applied gravity while jumping. */
	UPROPERTY(EditAnywhere)
	float JumpGravityMod = 1.f;
};
