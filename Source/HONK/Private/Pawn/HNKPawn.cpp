// Fill out your copyright notice in the Description page of Project Settings.

// HONK Includes
#include "Pawn/HNKPawn.h"

// Engine Includes
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pawn/HNKCharacterMoverComponent.h"

AHNKPawn::AHNKPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->InitCapsuleSize(35.f, 90.f);
	static FName PawnCollisionProfileName(TEXT("Pawn"));
	CapsuleComponent->SetCollisionProfileName(PawnCollisionProfileName);
	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	SetRootComponent(CapsuleComponent);

#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(CapsuleComponent);
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetSimulatePhysics(false);
	}
#endif // WITH_EDITORONLY_DATA
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->AlwaysLoadOnClient = true;
	Mesh->AlwaysLoadOnServer = true;
	Mesh->bOwnerNoSee = false;
	Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
	Mesh->bCastDynamicShadow = true;
	Mesh->bAffectDynamicIndirectLighting = true;
	Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	Mesh->SetupAttachment(CapsuleComponent);
	static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
	Mesh->SetCollisionProfileName(MeshCollisionProfileName);
	Mesh->SetGenerateOverlapEvents(false);
	Mesh->SetCanEverAffectNavigation(false);
	
	CharacterMoverComponent = CreateDefaultSubobject<UHNKCharacterMoverComponent>("CharacterMoverComponent");
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Disable bReplicateMovement because it interferes with the UMoverComponent's replication
	SetReplicatingMovement(false);
	
	// Lower the default NetUpdateFrequency because 100 is actually insane
	SetNetUpdateFrequency(30.f);
}

void AHNKPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHNKPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHNKPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHNKPawn::ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult)
{
	NativeProduceInput((float)SimTimeMs, InputCmdResult);
	
	if (bHasProduceInputinBpFunc)
	{
		InputCmdResult = BP_ProduceInput((float)SimTimeMs, InputCmdResult);
	}
}

void AHNKPawn::NativeProduceInput(float DeltaMs, FMoverInputCmdContext& OutInputCmd)
{
}

