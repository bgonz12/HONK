// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HNKGameplayAbility_MeleeAttack.h"

// HONK Includes
#include "Character/HNKCharacter.h"
#include "GAS/Abilities/Tasks/HNKAbilityTask_MeleeSweep.h"

// Engine Includes
#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/HNKPlayerCharacter.h"
#include "Player/HNKPlayerState.h"

UHNKGameplayAbility_MeleeAttack::UHNKGameplayAbility_MeleeAttack()
{
}

bool UHNKGameplayAbility_MeleeAttack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!bCanActivateWhileFalling)
	{
		if (AHNKCharacter* OwningCharacter = Cast<AHNKCharacter>(GetOwningActorFromActorInfo()))
		{
			if (UCharacterMovementComponent* MovementComponent = OwningCharacter->GetCharacterMovement())
			{
				if (MovementComponent->IsFalling())
				{
					return false;
				}
			}
		}
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UHNKGameplayAbility_MeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!Montage)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	
	// Collect attack windows from montage anim notifies
	for (const FAnimNotifyTrack& NotifyTrack : Montage->AnimNotifyTracks)
	{
		for (FAnimNotifyEvent* NotifyEvent : NotifyTrack.Notifies)
		{
			if (UHNKAnimNotifyState_MeleeAttackWindow* MeleeAttackWindow = Cast<UHNKAnimNotifyState_MeleeAttackWindow>(NotifyEvent->NotifyStateClass))
			{
				FHNKMeleeAttackWindow AttackWindow;
				MeleeAttackWindow->GetAttackWindow(AttackWindow);
				AttackWindow.BeginTime = NotifyEvent->GetTriggerTime();
				AttackWindow.EndTime = NotifyEvent->GetEndTriggerTime();
				
				AttackWindows.Add(AttackWindow);
			}
		}
	}
	
	if (AHNKCharacter* OwningCharacter = Cast<AHNKCharacter>(GetOwningActorFromActorInfo()))
	{
		if (USkeletalMeshComponent* MeshComponent = OwningCharacter->GetMesh())
		{
			for (const FHNKMeleeAttackWindow& AttackWindow : AttackWindows)
			{
				UHNKAbilityTask_MeleeSweep* MeleeSweepTask = UHNKAbilityTask_MeleeSweep::StartMeleeSweep(this, NAME_None, MeshComponent, AttackWindow);
				MeleeSweepTask->OnMeleeSweepHit.AddUniqueDynamic(this, &UHNKGameplayAbility_MeleeAttack::HandleMeleeSweepHit);
				MeleeSweepTask->ReadyForActivation();
				
				MeleeSweepTasks.Add(MeleeSweepTask);
			}
		}
	}
	
	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, Montage);
	MontageTask->OnCompleted.AddDynamic(this, &UHNKGameplayAbility_MeleeAttack::HandleMontageCompleted);
	MontageTask->OnCancelled.AddDynamic(this, &UHNKGameplayAbility_MeleeAttack::HandleMontageCancelledOrInterrupted);
	MontageTask->OnInterrupted.AddDynamic(this, &UHNKGameplayAbility_MeleeAttack::HandleMontageCancelledOrInterrupted);
	MontageTask->ReadyForActivation();
}

void UHNKGameplayAbility_MeleeAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	for (UHNKAbilityTask_MeleeSweep* MeleeSweepTask : MeleeSweepTasks)
	{
		if (MeleeSweepTask)
		{
			MeleeSweepTask->OnMeleeSweepHit.RemoveDynamic(this, &UHNKGameplayAbility_MeleeAttack::HandleMeleeSweepHit);
		}
	}
	
	AttackWindows.Reset();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHNKGameplayAbility_MeleeAttack::HandleMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UHNKGameplayAbility_MeleeAttack::HandleMontageCancelledOrInterrupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UHNKGameplayAbility_MeleeAttack::HandleMeleeSweepHit(const FHitResult& HitResult)
{
	if (!HasAuthority(&CurrentActivationInfo))
	{
		return;
	}
	
	UAbilitySystemComponent* OwnerASC = GetAbilitySystemComponentFromActorInfo();
	if (!OwnerASC)
	{
		return;
	}
	
	AHNKCharacter* OwnerCharacter = Cast<AHNKCharacter>(GetOwningActorFromActorInfo());
	if (!OwnerCharacter)
	{
		return;
	}
	
	AHNKPlayerState* OwnerPlayerState = nullptr;
	if (OwnerCharacter)
	{
		OwnerPlayerState = OwnerCharacter->GetPlayerState<AHNKPlayerState>();
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
	FakeHitResult.ImpactPoint = OwnerCharacter->GetActorLocation();
	
	FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext(CurrentSpecHandle, CurrentActorInfo);
	EffectContextHandle.AddHitResult(FakeHitResult);
	
	for (TSubclassOf<UGameplayEffect> EffectClass : HitEffects)
	{
		OwnerASC->ApplyGameplayEffectToTarget(EffectClass.GetDefaultObject(), TargetASC, UGameplayEffect::INVALID_LEVEL, EffectContextHandle);
	}
	
	if (IsValid(OwnerPlayerState))
	{
		OwnerPlayerState->TryTriggerGag(OwnerGagData);
	}
	
	if (AHNKPlayerCharacter* TargetCharacter = Cast<AHNKPlayerCharacter>(Actor))
	{
		if (AHNKPlayerState* TargetPlayerState = Cast<AHNKPlayerState>(TargetCharacter->GetPlayerState()))
		{
			TargetPlayerState->TryTriggerGag(TargetGagData);
		}
	}
}
