// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HNKCharacterMovementComponent.h"

// HONK Includes
#include "Character/HNKCharacter.h"

// Engine Includes
#include "GameFramework/GameNetworkManager.h"
#include "Net/UnrealNetwork.h"

void UHNKCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (APawn* OwnerPawn = GetOwner<APawn>())
	{
		if (OwnerPawn->IsLocallyControlled())
		{
			if (ShouldApplyJumpGravity())
			{
				if (!bApplyJumpGravity)
				{
					bApplyJumpGravity = true;
					Server_SetApplyJumpGravity(true);
				}
			}
			else
			{
				if (bApplyJumpGravity)
				{
					bApplyJumpGravity = false;
					Server_SetApplyJumpGravity(false);
				}
				
			}
		}
		
	}
}

void UHNKCharacterMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UHNKCharacterMovementComponent, bApplyJumpGravity);
}

float UHNKCharacterMovementComponent::GetGravityZ() const
{
	float GravityMod = FallingGravityMod;
	
	if (bApplyJumpGravity)
	{
		GravityMod = JumpGravityMod;
	}
	
	return Super::GetGravityZ() * GravityMod;
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

bool UHNKCharacterMovementComponent::ServerExceedsAllowablePositionError(float ClientTimeStamp, float DeltaTime, const FVector& Accel, const FVector& ClientWorldLocation, const FVector& RelativeClientLocation, UPrimitiveComponent* ClientMovementBase, FName ClientBaseBoneName, uint8 ClientMovementMode)
{
	// Check for disagreement in movement mode
	const uint8 CurrentPackedMovementMode = PackNetworkMovementMode();
	if (CurrentPackedMovementMode != ClientMovementMode)
	{
		// Consider this a major correction, see SendClientAdjustment()
		bNetworkLargeClientCorrection = true;
		return true;
	}

	const FVector LocDiff = UpdatedComponent->GetComponentLocation() - ClientWorldLocation;	
	
	// Check if we exceed the allowable position error
	bool bExceedsAllowablePositionError = false;
	if (OverrideAllowablePositionErrorSquared >= 0.f)
	{
		bExceedsAllowablePositionError = (LocDiff | LocDiff) > OverrideAllowablePositionErrorSquared;
	}
	else if (const AGameNetworkManager* GameNetworkManager = (const AGameNetworkManager*)(AGameNetworkManager::StaticClass()->GetDefaultObject()))
	{
		bExceedsAllowablePositionError = GameNetworkManager->ExceedsAllowablePositionError(LocDiff);
	}

	if (bExceedsAllowablePositionError)
	{
		bNetworkLargeClientCorrection |= (LocDiff.SizeSquared() > FMath::Square(NetworkLargeClientCorrectionDistance));
		return true;
	}
	
	return false;
}

void UHNKCharacterMovementComponent::Server_SetApplyJumpGravity_Implementation(bool bInApplyJumpGravity)
{
	bApplyJumpGravity = bInApplyJumpGravity;
}
