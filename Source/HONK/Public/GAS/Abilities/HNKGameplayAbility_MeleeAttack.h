// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "Animation/AnimNotifies/HNKAnimNotifyState_MeleeAttackWindow.h"
#include "GAS/Abilities/HNKGameplayAbility.h"
#include "HNKGameplayAbility_MeleeAttack.generated.h"

class UHNKGagDataAsset;
class UAnimMontage;
class UHNKAbilityTask_MeleeSweep;

/**
 * 
 */
UCLASS(Abstract)
class HONK_API UHNKGameplayAbility_MeleeAttack : public UHNKGameplayAbility
{
	GENERATED_BODY()
	
public:
	UHNKGameplayAbility_MeleeAttack();
	
	//~Begin UGameplayAbility
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	//~End UGameplayAbility

protected:
	//~Begin UGameplayAbility
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~End UGameplayAbility
	
	UFUNCTION()
	void HandleMontageCompleted();
	
	UFUNCTION()
	void HandleMontageCancelledOrInterrupted();
	
	UFUNCTION()
	void HandleMeleeSweepHit(const FHitResult& HitResult);
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> Montage;
	
	UPROPERTY(EditAnywhere)
	UHNKGagDataAsset* OwnerGagData;
	
	UPROPERTY(EditAnywhere)
	UHNKGagDataAsset* TargetGagData;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> HitEffects;
	
	UPROPERTY(EditAnywhere)
	bool bCanActivateWhileFalling = false;
	
	UPROPERTY()
	TArray<TObjectPtr<UHNKAbilityTask_MeleeSweep>> MeleeSweepTasks;
	
	TArray<FHNKMeleeAttackWindow> AttackWindows;
};
