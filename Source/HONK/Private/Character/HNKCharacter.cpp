// HONK Includes
#include "Character/HNKCharacter.h"

// GAS Includes
#include "AbilitySystemComponent.h"

// Engine Includes
#include "Character/HNKCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/HNKPlayerStateBase.h"

AHNKCharacter::AHNKCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UHNKCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(AscReplicationMode);
	
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

void AHNKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AHNKCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AHNKCharacter::InitializeAttributes()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC))
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = ASC->MakeOutgoingSpec(DefaultAttributes, 0, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
	}
}

void AHNKCharacter::LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	Super::LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
	
	bWasLaunched = true;
}

void AHNKCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	
	bWasLaunched = false;
}

void AHNKCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	HandlePlayerStateReady();
}

void AHNKCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	HandlePlayerStateReady();
}

void AHNKCharacter::HandlePlayerStateReady()
{
	if (HasAuthority())
	{
		if (AHNKPlayerStateBase* MyPlayerState = GetPlayerState<AHNKPlayerStateBase>())
		{
			//MyPlayerState->InitAbilitySystem();
			//InitializeAttributes();
		}
	}
}

