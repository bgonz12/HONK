// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifies/HNKAnimNotifyState_MeleeAttackWindow.h"
 
void UHNKAnimNotifyState_MeleeAttackWindow::DrawInEditor(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase*, const FAnimNotifyEvent& NotifyEvent) const
{
	if (!PDI || !MeshComp)
	{
		return;
	}
	
	const float PreviewTime = MeshComp->GetPosition();
	if (PreviewTime < NotifyEvent.GetTriggerTime() || PreviewTime > NotifyEvent.GetEndTriggerTime())
	{
		return;
	}
	
	FTransform OriginTransform = MeshComp->GetComponentTransform();
	if (AttackWindow.OriginSocketName != NAME_None)
	{
		OriginTransform = MeshComp->GetSocketTransform(AttackWindow.OriginSocketName, RTS_World);
	}
    
	const FVector BoxCenter = OriginTransform.TransformPositionNoScale(AttackWindow.LocalOffset);
	const FQuat BoxRotation = OriginTransform.GetRotation() * AttackWindow.LocalRotation.ToOrientationQuat();
	const FMatrix BoxMatrix = FTransform(BoxRotation, BoxCenter).ToMatrixNoScale();
	
	DrawOrientedWireBox(PDI,BoxMatrix.GetOrigin(),BoxMatrix.GetScaledAxis(EAxis::X),BoxMatrix.GetScaledAxis(EAxis::Y),BoxMatrix.GetScaledAxis(EAxis::Z), AttackWindow.HalfExtent, FLinearColor(1.0f, 0.25f, 0.0f), SDPG_Foreground, 3.0f);
}

void UHNKAnimNotifyState_MeleeAttackWindow::GetAttackWindow(FHNKMeleeAttackWindow& OutAttackWindow)
{
	OutAttackWindow = AttackWindow;
}
