// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// HONK Includes
#include "Character/HNKCharacter.h"
#include "Save/HNKSaveGame_Player.h"
#include "HNKPlayerCharacter.generated.h"

class UInputAction;

struct FHNKPlayerCosmeticsData;
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
class HONK_API AHNKPlayerCharacter : public AHNKCharacter
{
	GENERATED_BODY()
	
public:
	AHNKPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	
	//~Begin AActor
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~End AActor
	
	//~Begin APawn
	virtual void OnRep_Controller() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//~End APawn

protected:
	//~Begin APawn
	virtual void PossessedBy(AController* NewController) override;
	//~End APawn	
	
	virtual bool CanMove();
	
	virtual bool CanJump();
	
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_JumpStarted(const FInputActionValue& Value);
	void Input_JumpReleased(const FInputActionValue& Value);
	void Input_Ragdoll(const FInputActionValue& Value);
	
	UFUNCTION(Server, Reliable)
	void Server_StartRagdoll(const FVector& InRagdollLaunchVelocity);
	void StartRagdoll(const FVector& InRagdollLaunchVelocity);

	UFUNCTION(Server, Reliable)
	void Server_StopRagdoll();
	void StopRagdoll();

	UFUNCTION()
	void RagdollRecoverTimeEnd();
	
	UFUNCTION()
	void OnRep_RagdollProperties();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_RagdollPropertiesChanged();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_ScoreRagdollGag();
	
	virtual void TryInitPlayerCosmetics();
	
	UFUNCTION(Server, Reliable)
	virtual void Server_SetPlayerCosmetics(const FHNKPlayerCosmeticsData& InPlayerCosmetics);
	
	virtual void SetPlayerCosmetics(const FHNKPlayerCosmeticsData& InPlayerCosmetics);
	
	UFUNCTION()
	void OnRep_PlayerCosmetics();
	
	virtual void ApplyPlayerCosmetics(const FHNKPlayerCosmeticsData& InPlayerCosmetics);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> HairMesh;
	
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
	
	UPROPERTY(ReplicatedUsing=OnRep_PlayerCosmetics, EditAnywhere, BlueprintReadOnly, Category=Cosmetics)
	FHNKPlayerCosmeticsData PlayerCosmetics;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Cosmetics)
	TObjectPtr<USkeletalMesh> TEMP_JesterHatHairMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Cosmetics)
	TSubclassOf<UAnimInstance> TEMP_JesterHatAnimInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Cosmetics)
	TObjectPtr<USkeletalMesh> TEMP_PompadourHairMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Cosmetics)
	TSubclassOf<UAnimInstance> TEMP_PompadourAnimInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Cosmetics)
	TObjectPtr<USkeletalMesh> TEMP_FeminineBodyMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Cosmetics)
	TObjectPtr<USkeletalMesh> TEMP_MasculineBodyMesh;
};
