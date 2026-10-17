// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "Animation/AnimNotifies/AnimNotifyState.h"

// HONK Includes
#include "HNKAnimNotifyState_MeleeAttackWindow.generated.h"

USTRUCT(BlueprintType)
struct FHNKMeleeAttackWindow
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FName OriginSocketName = NAME_None;
	
	UPROPERTY(EditAnywhere)
	FVector LocalOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FVector LocalRotation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FVector HalfExtent = FVector(50.0f, 50.0f, 50.0f);
	
	float BeginTime = 0.f;
	float EndTime = 0.f;
};

/**
 * Provides the sweep data for performing melee attacks. It's intended to be used in conjunction with
 * melee attack gameplay abilities and does not perform collision sweeps itself or apply damage effects.
 */
UCLASS(DisplayName="HNKMeleeAttackWindow")
class HONK_API UHNKAnimNotifyState_MeleeAttackWindow : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	//~Begin UAnimNotifyState
	virtual void DrawInEditor(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const override;
	//~End UAnimNotifyState
	
	void GetAttackWindow(FHNKMeleeAttackWindow& OutAttackWindow);
	
protected:
	UPROPERTY(EditAnywhere)
	FHNKMeleeAttackWindow AttackWindow;
};
