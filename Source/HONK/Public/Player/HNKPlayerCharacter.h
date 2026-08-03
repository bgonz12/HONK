// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "Character/HNKCharacterBase.h"
#include "HNKPlayerCharacter.generated.h"

class UInputAction;
struct FInputActionValue;

/**
 * Storing this in a struct to ensure clients receive all data when ragdoll state changes.
 */
USTRUCT(BlueprintType)
struct FHNKRagdollData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	bool bIsInRagdoll = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool bCanRecoverFromRagdoll = false;
	
	UPROPERTY(BlueprintReadWrite)
	FVector RagdollLaunchVelocity = FVector::ZeroVector;
};

UCLASS()
class HONK_API AHNKPlayerCharacter : public AHNKCharacterBase
{
	GENERATED_BODY()
	
public:
	//~Begin AActor
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~End AActor
	
	//~Begin APawn
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//~End APawn

protected:
	virtual bool CanMove();
	
	virtual bool CanJump();
	
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_JumpStarted(const FInputActionValue& Value);
	void Input_JumpReleased(const FInputActionValue& Value);
	void Input_Ragdoll(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Server_StartRagdoll(const FVector& InRagdollLaunchVelocity);
	
	UFUNCTION(Server, Reliable)
	void Server_StopRagdoll();
	
	UFUNCTION()
	void RagdollRecoverTimeEnd();
	
	UFUNCTION()
	void OnRep_RagdollProperties();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_RagdollPropertiesChanged();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_ScoreRagdollGag();
	
protected:
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> MoveInputAction;
   
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> LookInputAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> JumpInputAction;
	
	/** Ragdoll Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> RagdollInputAction;
	
	UPROPERTY(ReplicatedUsing=OnRep_RagdollProperties, VisibleAnywhere, BlueprintReadWrite)
	FHNKRagdollData RagdollData;
	
	FTimerHandle RagdollRecoverTimerHandle;
};
