// Fill out your copyright notice in the Description page of Project S.ettings.

#include "Inventory/Projectile/HNKProjectile.h"

// HONK Includes
#include "Character/HNKCharacter.h"

// Engine Includes
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Player/HNKPlayerCharacter.h"
#include "Player/HNKPlayerState.h"

// Sets default values
AHNKProjectile::AHNKProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(FName("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(FName("Projectile"));
	CollisionComponent->InitSphereRadius(50.f);
	SetRootComponent(CollisionComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->MaxSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	
	InitialLifeSpan = 10.f;
}

void AHNKProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorHit.AddDynamic(this, &AHNKProjectile::ActorHit);
}

void AHNKProjectile::ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileImpact(Hit);
}

void AHNKProjectile::ProjectileImpact(const FHitResult& Hit)
{
	FString HitActorName = Hit.GetActor() ? Hit.GetActor()->GetName() : TEXT("");
	FString HitComponentName = Hit.GetComponent() ? Hit.GetComponent()->GetName() : TEXT("");
	UE_LOG(LogTemp, Warning, TEXT("Projectile Impact: %s HitActor: %s HitComponent: %s"), *GetName(), *HitActorName, *HitComponentName);
	
	ApplyHitEffects(Hit);
	
	Destroy();
}

USphereComponent* AHNKProjectile::GetCollisionComponent() const
{
	return CollisionComponent;
}

void AHNKProjectile::ApplyHitEffects(const FHitResult& HitResult)
{
	if (GetNetMode() == NM_Client)
	{
		return;
	}
	
	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	if (!OwnerASC)
	{
		return;
	}
	
	AHNKCharacter* OwnerCharacter = Cast<AHNKCharacter>(OwnerASC->GetAvatarActor());
	if (!OwnerCharacter)
	{
		return;
	}
	
	AActor* Actor = HitResult.GetActor();
	if (!Actor)
	{
		return;
	}
		
	UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor);
	if (!TargetASC)
	{
		return;
	}
	
	// Adding this so the hit character is always launched away from the attacker.
	// Might consider adding a checkbox for this.
	FHitResult FakeHitResult = HitResult;
	FakeHitResult.TraceStart = OwnerCharacter->GetActorLocation();
	
	FGameplayEffectContextHandle EffectContextHandle = OwnerASC->MakeEffectContext();
	EffectContextHandle.AddHitResult(FakeHitResult);
	
	for (TSubclassOf<UGameplayEffect> EffectClass : HitEffects)
	{
		OwnerASC->ApplyGameplayEffectToTarget(EffectClass.GetDefaultObject(), TargetASC, UGameplayEffect::INVALID_LEVEL, EffectContextHandle);
	}
	
	if (OwnerGagData)
	{
		AHNKPlayerState* OwnerPlayerState = OwnerCharacter->GetPlayerState<AHNKPlayerState>();
		if (IsValid(OwnerPlayerState))
		{
			OwnerPlayerState->TryTriggerGag(OwnerGagData);
		}
	}
	
	if (TargetGagData)
	{
		if (AHNKPlayerCharacter* TargetCharacter = Cast<AHNKPlayerCharacter>(Actor))
		{
			if (AHNKPlayerState* TargetPlayerState = Cast<AHNKPlayerState>(TargetCharacter->GetPlayerState()))
			{
				TargetPlayerState->TryTriggerGag(TargetGagData);
			}
		}
	}
}
