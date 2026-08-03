// Fill out your copyright notice in the Description page of Project Settings.

// HONK Includes
#include "Player/HNKPlayerCharacter.h"

// Engine Includes
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

void AHNKPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AHNKPlayerCharacter, RagdollData);
}

void AHNKPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{	
		Input->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AHNKPlayerCharacter::Input_Move);
		Input->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AHNKPlayerCharacter::Input_Look);
		Input->BindAction(JumpInputAction, ETriggerEvent::Started, this, &AHNKPlayerCharacter::Input_JumpStarted);
		Input->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &AHNKPlayerCharacter::Input_JumpReleased);
		Input->BindAction(RagdollInputAction, ETriggerEvent::Triggered, this, &AHNKPlayerCharacter::Input_Ragdoll);
	}
}

bool AHNKPlayerCharacter::CanMove()
{
	return !RagdollData.bIsInRagdoll;
}

bool AHNKPlayerCharacter::CanJump()
{
	return true;
}

void AHNKPlayerCharacter::Input_Move(const FInputActionValue& Value)
{
	const FVector MovementVector = Value.Get<FVector>();
	
	if (CanMove())
	{
		FRotator ControlRotationZ = GetControlRotation();
		ControlRotationZ.Pitch = 0.f;
	
		AddMovementInput(UKismetMathLibrary::GetRightVector(ControlRotationZ), MovementVector.Y);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(ControlRotationZ), MovementVector.X);
	}
}

void AHNKPlayerCharacter::Input_Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	
	AddControllerPitchInput(-LookVector.Y);
	AddControllerYawInput(LookVector.X);
}

void AHNKPlayerCharacter::Input_JumpStarted(const FInputActionValue& Value)
{
	if (CanJump())
	{
		if (RagdollData.bIsInRagdoll)
		{
			Server_StopRagdoll();
		}
		else
		{
			Jump();
		}
	}
}

void AHNKPlayerCharacter::Input_JumpReleased(const FInputActionValue& Value)
{
	StopJumping();
}

void AHNKPlayerCharacter::Input_Ragdoll(const FInputActionValue& Value)
{
	if (UCapsuleComponent* MyCapsule = GetCapsuleComponent())
	{
		BP_ScoreRagdollGag();
		Server_StartRagdoll(MyCapsule->GetComponentVelocity());
	}
}

void AHNKPlayerCharacter::Server_StartRagdoll_Implementation(const FVector& InRagdollLaunchVelocity)
{
	if (!RagdollData.bIsInRagdoll)
	{
		RagdollData.bCanRecoverFromRagdoll = false;
		
		RagdollData.RagdollLaunchVelocity = InRagdollLaunchVelocity;
		RagdollData.bIsInRagdoll = true;
		OnRep_RagdollProperties(); // Call this for the server
		
		GetWorldTimerManager().SetTimer(RagdollRecoverTimerHandle, this, &AHNKPlayerCharacter::RagdollRecoverTimeEnd, 1.f);
	}
}

void AHNKPlayerCharacter::RagdollRecoverTimeEnd()
{
	RagdollData.bCanRecoverFromRagdoll = true;
}

void AHNKPlayerCharacter::OnRep_RagdollProperties()
{
	BP_RagdollPropertiesChanged();
}

void AHNKPlayerCharacter::Server_StopRagdoll_Implementation()
{
	if (RagdollData.bIsInRagdoll && RagdollData.bCanRecoverFromRagdoll)
	{
		RagdollData.bIsInRagdoll = false;
		RagdollData.RagdollLaunchVelocity = FVector::ZeroVector;
		OnRep_RagdollProperties(); // Call this for the server
	}
}
