// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "Abilities/Tasks/AbilityTask.h"
#include "Animation/AnimNotifies/HNKAnimNotifyState_MeleeAttackWindow.h"

// HONK Includes
#include "HNKAbilityTask_MeleeSweep.generated.h"

class UGameplayAbility;
class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHNKMeleeSweepHit, const FHitResult&, HitResult);

UCLASS()
class HONK_API UHNKAbilityTask_MeleeSweep : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	static UHNKAbilityTask_MeleeSweep* StartMeleeSweep(UGameplayAbility* OwningAbility, FName TaskInstanceName, USkeletalMeshComponent* MeshComponent, const FHNKMeleeAttackWindow& AttackWindow);
	
	UHNKAbilityTask_MeleeSweep();
	
	//~Begin UGameplayTask
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	//~End UGameplayTask
	
protected:
	//~Begin UGameplayTask
	virtual void Activate() override;
	//~End UGameplayTask
	
	UFUNCTION()
	void StartSweeping();
	
	UFUNCTION()
	void StopSweeping();
	
public:
	UPROPERTY(BlueprintAssignable)
	FHNKMeleeSweepHit OnMeleeSweepHit;
	
protected:
	// Input Properties
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> MeshComponent;
	
	FHNKMeleeAttackWindow AttackWindow;
	
	// Runtime Properties
	UPROPERTY()
	TArray<AActor*> IgnoreActors;
	
	FTimerHandle SweepingTimerHandle;
	
	FVector PrevBoxCenter = FVector::ZeroVector;
	
	bool bIsSweeping = false;	
};
