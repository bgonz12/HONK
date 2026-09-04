// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
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
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//~ Begin UActorComponent
	virtual float GetGravityZ() const override;
	//~ End UActorComponent
	
	bool ShouldApplyJumpGravity() const;
	
	UFUNCTION(Server, Reliable)
	void Server_SetApplyJumpGravity(bool bInApplyJumpGravity);
	
protected:
	virtual bool ServerExceedsAllowablePositionError(float ClientTimeStamp, float DeltaTime, const FVector& Accel, const FVector& ClientWorldLocation, const FVector& RelativeClientLocation, UPrimitiveComponent* ClientMovementBase, FName ClientBaseBoneName, uint8 ClientMovementMode) override;
	
protected:
	/** Modifier applied gravity while falling. */
	UPROPERTY(EditAnywhere)
	float FallingGravityMod = 1.f;
	
	/** Modifier applied gravity while jumping. */
	UPROPERTY(EditAnywhere)
	float JumpGravityMod = 1.f;
	
	/** Client needs to replicate this to the server so they don't desync from fall gravity. */
	UPROPERTY(Replicated, VisibleAnywhere)
	bool bApplyJumpGravity = false;
	
	UPROPERTY(Category="Character Movement (Networking)", EditDefaultsOnly, meta=(ClampMin="0.0", UIMin="0.0", ForceUnits=cm))
	float OverrideAllowablePositionErrorSquared = -1.f;

};
