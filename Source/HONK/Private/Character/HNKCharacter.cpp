
#include "Character/HNKCharacter.h"

// HONK Includes
#include "Character/HNKCharacterMovementComponent.h"
#include "GAS/Attribute/HNKHealthAttributeSet.h"
#include "GAS/HNKGameplayTags.h"

// Engine Includes
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AHNKCharacter::AHNKCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UHNKCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Lower the default NetUpdateFrequency because 100 is actually insane
	SetNetUpdateFrequency(30.f);

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
	
	// Setup attribute sets
	HealthAttributeSet = CreateDefaultSubobject<UHNKHealthAttributeSet>(TEXT("HealthAttributeSet"));
}

void AHNKCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		FOnGameplayEffectTagCountChanged& AimingTagChangedEvent = ASC->RegisterGameplayTagEvent(HNKGameplayTags::Ability_State_Aiming, EGameplayTagEventType::NewOrRemoved);
		AimingTagChangedDelegateHandle = AimingTagChangedEvent.AddUObject(this, &AHNKCharacter::AimingTagChanged);
	}
	
	Super::EndPlay(EndPlayReason);
}

void AHNKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AHNKCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AHNKCharacter::InitializeAbilitySystem()
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		ASC->InitAbilityActorInfo(GetController(), this);
		HealthAttributeSet = ASC->GetSet<UHNKHealthAttributeSet>();
	}
}

void AHNKCharacter::InitializeAttributes()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC)
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

void AHNKCharacter::GameplayCue_PlaySound(EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	if (const USoundBase* Sound = Cast<USoundBase>(Parameters.SourceObject))
	{
		USoundBase* SoundToPlay = const_cast<USoundBase*>(Sound);
		UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation());
	}
}

void AHNKCharacter::HandleControllerReady()
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		FOnGameplayEffectTagCountChanged& AimingTagChangedEvent = ASC->RegisterGameplayTagEvent(HNKGameplayTags::Ability_State_Aiming, EGameplayTagEventType::NewOrRemoved);
		AimingTagChangedDelegateHandle = AimingTagChangedEvent.AddUObject(this, &AHNKCharacter::AimingTagChanged);
	}
}

void AHNKCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitializeAbilitySystem();
	InitializeAttributes();
	
	HandleControllerReady(); // Call on server
}

void AHNKCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();
	
	HandleControllerReady(); // Call on client
}

void AHNKCharacter::AimingTagChanged(const FGameplayTag GameplayTag, int32 NewCount)
{
	if (UCharacterMovementComponent* MyCharacterMovement = GetCharacterMovement())
	{
		if (bIsAiming)
		{
			if (NewCount <= 0)
			{
				bIsAiming = false;
				// TODO: Consider adding state request system with priorities for controlling bOrientRotationToMovement
				MyCharacterMovement->bOrientRotationToMovement = !bIsAiming;
				
				BP_AimingChanged();
			}
		}
		else
		{
			if (NewCount > 0)
			{
				bIsAiming = true;
				MyCharacterMovement->bOrientRotationToMovement = !bIsAiming;

				BP_AimingChanged();
			}
		}
	}
}

