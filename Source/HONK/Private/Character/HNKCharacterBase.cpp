// HONK Includes
#include "Character/HNKCharacterBase.h"

// GAS Includes
#include "AbilitySystemComponent.h"

// Engine Includes
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/HNKPlayerStateBase.h"

AHNKCharacterBase::AHNKCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Init capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 90.f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Init character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
}

void AHNKCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHNKCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHNKCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AHNKCharacterBase::GetAbilitySystemComponent() const
{
	if (AHNKPlayerStateBase* MyPlayerState = GetPlayerState<AHNKPlayerStateBase>())
	{
		return MyPlayerState->GetAbilitySystemComponent();
	}
	
	return nullptr;
}

void AHNKCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AHNKCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

