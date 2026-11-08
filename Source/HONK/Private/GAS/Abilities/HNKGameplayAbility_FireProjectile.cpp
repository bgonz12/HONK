// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HNKGameplayAbility_FireProjectile.h"

// HONK Includes
#include "Character/HNKCharacter.h"
#include "GAS/HNKGameplayTags.h"
#include "Inventory/HNKInventoryStatics.h"
#include "Inventory/Equipment/HNKEquipmentAttachment.h"
#include "Inventory/Equipment/HNKEquipmentComponent.h"
#include "Inventory/Equipment/HNKEquipmentInstance.h"
#include "Player/HNKPlayerCharacter.h"

// Engine Includes
#include "Abilities/GameplayAbilityTargetActor_SingleLineTrace.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Inventory/Projectile/HNKProjectileFireComponent.h"
#include "Kismet/KismetMathLibrary.h"

UHNKGameplayAbility_FireProjectile::UHNKGameplayAbility_FireProjectile()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UHNKGameplayAbility_FireProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AHNKCharacter* OwnerCharacter = Cast<AHNKCharacter>(GetAvatarActorFromActorInfo());
	if (!OwnerCharacter)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	APlayerController* OwnerController = OwnerCharacter->GetController<APlayerController>();
	if (!OwnerController)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	TSubclassOf<AGameplayAbilityTargetActor> TargetActorClass = AGameplayAbilityTargetActor_SingleLineTrace::StaticClass();
	
	// Need to use TargetData so clients can provide aim direction to the server
	UAbilityTask_WaitTargetData* AbilityTask = UAbilityTask_WaitTargetData::WaitTargetData(this, NAME_None, EGameplayTargetingConfirmation::Instant, TargetActorClass);
	AbilityTask->ValidData.AddDynamic(this, &UHNKGameplayAbility_FireProjectile::TargetDataReady);
	AbilityTask->Cancelled.AddDynamic(this, &UHNKGameplayAbility_FireProjectile::TargetDataCancelled);
	
	AGameplayAbilityTargetActor* TargetActor = nullptr;
	if (AbilityTask->BeginSpawningActor(this, TargetActorClass,TargetActor))
	{
		if (AGameplayAbilityTargetActor_SingleLineTrace* TargetActorSingleLineTrace = Cast<AGameplayAbilityTargetActor_SingleLineTrace>(TargetActor))
		{
			// Calculate spawn transform
			FVector CameraLocation = FVector::ZeroVector;
			FRotator CameraRotation = FRotator::ZeroRotator;
			OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
		
			FVector AimLocation = CameraLocation + UKismetMathLibrary::GetForwardVector(CameraRotation) * 8000.f;
	
			FTransform SpawnTransform = FTransform::Identity;
			GetSpawnTransform(AimLocation, SpawnTransform);
			
			// Provide SpawnTransform to TargetActor
			TargetActorSingleLineTrace->StartLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
			TargetActorSingleLineTrace->StartLocation.LiteralTransform = SpawnTransform;
			TargetActorSingleLineTrace->MaxRange = 8000.f;
		
			AbilityTask->FinishSpawningActor(this, TargetActor);
		}
	}
	
	// Activate on both server and client
	if (AbilityTask)
	{
		AbilityTask->ReadyForActivation();
	}
}

void UHNKGameplayAbility_FireProjectile::GetSpawnTransform(const FVector& InAimLocation, FTransform& OutSpawnTransform) const
{
	AHNKCharacter* OwnerCharacter = Cast<AHNKCharacter>(GetAvatarActorFromActorInfo());
	if (!OwnerCharacter)
	{
		return;
	}
	
	if (UHNKEquipmentComponent* EquipmentComponent = UHNKInventoryStatics::GetEquipmentComponentFromActor(OwnerCharacter))
	{
		if (UHNKEquipmentInstance* EquipmentInstance = EquipmentComponent->FindEquipmentInSlot(HNKGameplayTags::Equipment_Slot_MainHand))
		{
			if (EquipmentInstance->AttachmentActor)
			{
				EquipmentInstance->AttachmentActor->GetProjectileSpawnTransform(OutSpawnTransform);
			}
		}
	}
	
	FVector AimDir = (InAimLocation - OutSpawnTransform.GetLocation()).GetSafeNormal();
	OutSpawnTransform.SetRotation(AimDir.ToOrientationQuat());
}

void UHNKGameplayAbility_FireProjectile::TargetDataReady(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (const FGameplayAbilityTargetData* TargetData = TargetDataHandle.Get(0))
	{
		FTransform SpawnTransform = TargetData->GetOrigin();
		GetSpawnTransform(TargetData->GetEndPoint(), SpawnTransform);
		
		if (AHNKPlayerCharacter* PlayerCharacter = Cast<AHNKPlayerCharacter>(GetAvatarActorFromActorInfo()))
		{
			if (UHNKProjectileFireComponent* ProjectileFireComponent = PlayerCharacter->GetProjectileFireComponent())
			{
				if (PlayerCharacter->HasAuthority())
				{
					ProjectileFireComponent->Multicast_SpawnProjectile(ProjectileClass, SpawnTransform);
				}
				else
				{
					ProjectileFireComponent->SpawnProjectile(ProjectileClass, SpawnTransform);
				}
			}
		}
	}
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UHNKGameplayAbility_FireProjectile::TargetDataCancelled(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
