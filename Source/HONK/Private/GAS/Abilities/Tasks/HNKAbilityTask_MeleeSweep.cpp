// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Abilities/Tasks/HNKAbilityTask_MeleeSweep.h"

// Engine Includes
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

#define COLLISION_WEAPON ECC_GameTraceChannel2

static TAutoConsoleVariable<bool> CVarShowMeleeSweeps(TEXT("hnk.Weapon.ShowMeleeSweeps"), false, TEXT("Enables debug draws for melee sweeps."));

UHNKAbilityTask_MeleeSweep* UHNKAbilityTask_MeleeSweep::StartMeleeSweep(
	UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	USkeletalMeshComponent* MeshComponent,
	const FHNKMeleeAttackWindow& AttackWindow)
{
	UHNKAbilityTask_MeleeSweep* MyObj = NewAbilityTask<UHNKAbilityTask_MeleeSweep>(OwningAbility, TaskInstanceName);
	MyObj->MeshComponent = MeshComponent;
	MyObj->AttackWindow = AttackWindow;
	
	if (MeshComponent)
	{
		MyObj->IgnoreActors.Add(MeshComponent->GetOwner());
	}
	
	return MyObj;
}

UHNKAbilityTask_MeleeSweep::UHNKAbilityTask_MeleeSweep()
{
	bTickingTask = true;
}

void UHNKAbilityTask_MeleeSweep::Activate()
{
	Super::Activate();
	
	if (UWorld* World = GetWorld())
	{
		const float InitialDelay = AttackWindow.BeginTime;
		World->GetTimerManager().SetTimer(SweepingTimerHandle, this, &UHNKAbilityTask_MeleeSweep::StartSweeping,InitialDelay);
	}
}

void UHNKAbilityTask_MeleeSweep::TickTask(float DeltaTime)
{
	if (!bIsSweeping)
	{
		return;
	}
	
	if (!MeshComponent)
	{
		return;
	}
	
	FTransform SocketTransform = MeshComponent->GetComponentTransform();
	if (AttackWindow.OriginSocketName != NAME_None)
	{
		SocketTransform = MeshComponent->GetSocketTransform(AttackWindow.OriginSocketName, RTS_World);
	}
    
	const FVector BoxCenter = SocketTransform.TransformPositionNoScale(AttackWindow.LocalOffset);
	const FVector BoxExtent = AttackWindow.HalfExtent;
	const FQuat BoxRotation = SocketTransform.GetRotation() * AttackWindow.LocalRotation.ToOrientationQuat();
	
	EDrawDebugTrace::Type DrawDebugType = CVarShowMeleeSweeps.GetValueOnAnyThread() ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
	
	FHitResult HitResult;
	if (UKismetSystemLibrary::BoxTraceSingle(this, PrevBoxCenter, BoxCenter, BoxExtent, BoxRotation.Rotator(), UEngineTypes::ConvertToTraceType(COLLISION_WEAPON), false, IgnoreActors, DrawDebugType, HitResult, true, FLinearColor::Red, FLinearColor::Green, 3.f))
	{
		OnMeleeSweepHit.Broadcast(HitResult);
		
		if (HitResult.GetActor())
		{
			IgnoreActors.Add(HitResult.GetActor());
		}
	}
	
	PrevBoxCenter = BoxCenter;
}

void UHNKAbilityTask_MeleeSweep::OnDestroy(bool bInOwnerFinished)
{
	if (SweepingTimerHandle.IsValid())
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(SweepingTimerHandle);
		}
		
		SweepingTimerHandle.Invalidate();
	}
	
	Super::OnDestroy(bInOwnerFinished);
}

void UHNKAbilityTask_MeleeSweep::StartSweeping()
{
	bIsSweeping = true;
	
	if (UWorld* World = GetWorld())
	{
		const float SweepDuration = AttackWindow.EndTime - AttackWindow.BeginTime;
		World->GetTimerManager().SetTimer(SweepingTimerHandle, this, &UHNKAbilityTask_MeleeSweep::StopSweeping, SweepDuration);
	}
	
	FTransform SocketTransform = MeshComponent->GetComponentTransform();
	if (AttackWindow.OriginSocketName != NAME_None)
	{
		SocketTransform = MeshComponent->GetSocketTransform(AttackWindow.OriginSocketName, RTS_World);
	}
    
	PrevBoxCenter = SocketTransform.TransformPositionNoScale(AttackWindow.LocalOffset);
}

void UHNKAbilityTask_MeleeSweep::StopSweeping()
{
	bIsSweeping = false;

	EndTask();
}
