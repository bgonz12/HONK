// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/HNKPlayerCharacter.h"

// HONK Includes
#include "Save/HNKSaveGame_Player.h"
#include "Save/HNKSaveGameSubsystem.h"

// Engine Includes
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

AHNKPlayerCharacter::AHNKPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	HairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	HairMesh->SetupAttachment(GetMesh());
}

void AHNKPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AHNKPlayerCharacter, RagdollData);
}

void AHNKPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	TryInitPlayerCosmetics();
}


void AHNKPlayerCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();
	
	TryInitPlayerCosmetics();
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
	if (!RagdollData.bIsInRagdoll)
	{
		if (UCapsuleComponent* MyCapsule = GetCapsuleComponent())
		{
			FVector RagdollVelocity = MyCapsule->GetComponentVelocity();

			Server_StartRagdoll(RagdollVelocity);
			StartRagdoll(RagdollVelocity);
		}
	}
}

void AHNKPlayerCharacter::Server_StartRagdoll_Implementation(const FVector& InRagdollLaunchVelocity)
{
	if (!RagdollData.bIsInRagdoll)
	{
		BP_ScoreRagdollGag();
		StartRagdoll(InRagdollLaunchVelocity);
	}
}

void AHNKPlayerCharacter::StartRagdoll(const FVector& InRagdollLaunchVelocity)
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

void AHNKPlayerCharacter::Server_StopRagdoll_Implementation()
{
	StopRagdoll();
}

void AHNKPlayerCharacter::StopRagdoll()
{
	if (RagdollData.bIsInRagdoll && RagdollData.bCanRecoverFromRagdoll)
	{
		RagdollData.bIsInRagdoll = false;
		RagdollData.RagdollLaunchVelocity = FVector::ZeroVector;
		OnRep_RagdollProperties(); // Call this for the server
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

void AHNKPlayerCharacter::TryInitPlayerCosmetics()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC || !PC->IsLocalPlayerController())
	{
		return;
	}
	
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
	{
		if (UHNKSaveGameSubsystem* SaveGameSubsystem = GameInstance->GetSubsystem<UHNKSaveGameSubsystem>())
		{
			if (UHNKSaveGame_Player* PlayerSaveGame = Cast<UHNKSaveGame_Player>(SaveGameSubsystem->GetSaveGameInstance(EHNKSaveType::ST_Player)))
			{
				if (!PlayerSaveGame->PlayerCosmetics.IsValid())
				{
					SanitizePlayerCosmetics(PlayerSaveGame->PlayerCosmetics);
				}
				
				Server_SetPlayerCosmetics(PlayerSaveGame->PlayerCosmetics);
			}
		}
	}
}

void AHNKPlayerCharacter::Server_SetPlayerCosmetics_Implementation(const FHNKPlayerCosmeticsData& InPlayerCosmetics)
{
	SetPlayerCosmetics(InPlayerCosmetics);
}

void AHNKPlayerCharacter::SetPlayerCosmetics(const FHNKPlayerCosmeticsData& InPlayerCosmetics)
{
	PlayerCosmetics = InPlayerCosmetics;
	OnRep_PlayerCosmetics();
}

void AHNKPlayerCharacter::OnRep_PlayerCosmetics()
{
	ApplyPlayerCosmetics(PlayerCosmetics);
}

void AHNKPlayerCharacter::ApplyPlayerCosmetics(const FHNKPlayerCosmeticsData& InPlayerCosmetics)
{
	BP_ApplyPlayerCosmetics(InPlayerCosmetics);
}

void AHNKPlayerCharacter::SanitizePlayerCosmetics(FHNKPlayerCosmeticsData& InPlayerCosmetics)
{
	if (!InPlayerCosmetics.BodyType.IsValid())
	{
		InPlayerCosmetics.BodyType = DefaultPlayerCosmetics.BodyType;
	}
	
	if (!InPlayerCosmetics.HairType.IsValid())
	{
		InPlayerCosmetics.HairType = DefaultPlayerCosmetics.HairType;
	}
	
	if (!InPlayerCosmetics.HairColor.IsValid())
	{
		InPlayerCosmetics.HairColor = DefaultPlayerCosmetics.HairColor;
	}

	if (!InPlayerCosmetics.EyesType.IsValid())
	{
		InPlayerCosmetics.EyesType = DefaultPlayerCosmetics.EyesType;
	}
	
	if (!InPlayerCosmetics.EyeColor.IsValid())
	{
		InPlayerCosmetics.EyeColor = DefaultPlayerCosmetics.EyeColor;
	}
	
	if (!InPlayerCosmetics.MouthType.IsValid())
	{
		InPlayerCosmetics.MouthType = DefaultPlayerCosmetics.MouthType;
	}
}
