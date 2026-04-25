// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

// HONK Includes
#include "HKPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHKOnRep_Pawn_Signature, const AHKPlayerController*, HKPlayerController);

UCLASS()
class HONK_API AHKPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlayingState() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "HKPlayerController")
	void BP_BeginPlayingState();

	virtual void OnRep_Pawn() override;
	UFUNCTION(BlueprintImplementableEvent, Category = "HKPlayerController|Pawn")
	void BP_OnRep_Pawn();

	virtual void OnRep_PlayerState() override;
	UFUNCTION(BlueprintImplementableEvent, Category = "HKPlayerController|Pawn")
	void BP_OnRep_PlayerState();

public:
	UPROPERTY(BlueprintAssignable)
	FHKOnRep_Pawn_Signature OnRep_Pawn_Delegate;
};
