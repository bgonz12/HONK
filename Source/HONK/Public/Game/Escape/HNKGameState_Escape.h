// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "Game/HNKGameState.h"
#include "Save/HNKSaveableObjectInterface.h"

#include "HNKGameState_Escape.generated.h"

class APlayerController;

UENUM(BlueprintType)
enum class EHNKEscapeState : uint8
{
	ES_None,
	ES_BuildMode,
	ES_Performance,
	ES_DaySummary,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHNKEscapeStateChanged, AHNKGameState_Escape*, GameState, EHNKEscapeState, NewEscapeState);

UCLASS()
class HONK_API AHNKGameState_Escape : public AHNKGameState, public IHNKSaveableObjectInterface
{
	GENERATED_BODY()
	
public:
	//~ Begin UObject
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const override;
	//~ End UObject

	//~ Begin AHNKGameState
	virtual void Server_PlayerReadyUp(APlayerController* PlayerController) override;
	virtual void Server_PlayerUnreadyUp(APlayerController* PlayerController) override;
	//~ End AHNKGameState
	
	//~Begin IHNKSaveableObjectInterface
	virtual void SaveObject(USaveGame* SaveGame) override;
	virtual void LoadObject(USaveGame* SaveGame) override;
	//~End IHNKSaveableObjectInterface
	
	void SetCurrentEscapeState(const EHNKEscapeState& InEscapeState);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_CurrentEscapeStateChanged(const EHNKEscapeState& NewEscapeState);
	
	UFUNCTION(BlueprintCallable)
	void SetTimeRemaining(float InTimeRemaining);

	UFUNCTION()
	void OnRep_CurrentEscapeState();
	
public:
	UPROPERTY(BlueprintAssignable)
	FHNKEscapeStateChanged OnEscapeStateChanged;
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentEscapeState, BlueprintReadOnly, VisibleAnywhere)
	EHNKEscapeState CurrentEscapeState = EHNKEscapeState::ES_None;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeRemaining = 0.f;
	
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
	int32 CurrentDay = 0;
	
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
	int32 CurrentMoney = 0;
};
