// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HNKCharacterMovementComponent.h"

// HONK Includes
#include "Character/HNKCharacter.h"

float UHNKCharacterMovementComponent::GetGravityZ() const
{
	float JumpMod = 1.f;
	
	if (JumpGravityMod != 1.f)
	{
		if (ShouldApplyJumpGravity())
		{
			JumpMod = JumpGravityMod;
		}
	}
	
	return Super::GetGravityZ() * JumpMod;
}

bool UHNKCharacterMovementComponent::ShouldApplyJumpGravity() const
{
	if (AHNKCharacter* Character = GetOwner<AHNKCharacter>())
	{
		if (Character->GetWasLaunched())
		{
			return true;
		}
		else if (Velocity.Z > 0.f && Character->JumpKeyHoldTime > 0.f)
		{
			return true;
		}
	}
	
	return false;
}
