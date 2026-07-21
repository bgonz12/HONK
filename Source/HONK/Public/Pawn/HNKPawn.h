// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "MoverSimulationTypes.h"
#include "GameFramework/Pawn.h"

// HONK Includes
#include "HNKPawn.generated.h"

class UArrowComponent;
class UCapsuleComponent;
class UHNKCharacterMoverComponent;
class USkeletalMeshComponent;

UCLASS()
class HONK_API AHNKPawn : public APawn, public IMoverInputProducerInterface
{
	GENERATED_BODY()

public:
	AHNKPawn();

	/** AActor */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult) override;

	// Override this function in native class to author input for the next simulation frame. Consider also calling Super method.
	virtual void NativeProduceInput(float DeltaMs, FMoverInputCmdContext& OutInputCmd);

	// Implement this event in Blueprints to author input for the next simulation frame. Consider also calling Parent event.
	UFUNCTION(BlueprintImplementableEvent, meta = (ScriptName = "OnProduceInput"))
	FMoverInputCmdContext BP_ProduceInput(float DeltaMs, FMoverInputCmdContext& InputCmd);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HNKPawn")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
#if WITH_EDITORONLY_DATA
	/** Component shown in the editor only to indicate character facing */
	UPROPERTY()
	TObjectPtr<UArrowComponent> ArrowComponent;
#endif
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HNKPawn")
	TObjectPtr<USkeletalMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HNKPawn")
	TObjectPtr<UHNKCharacterMoverComponent> CharacterMoverComponent;
	
	uint8 bHasProduceInputinBpFunc : 1;
};
