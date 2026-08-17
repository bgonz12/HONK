// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "GameFramework/GameState.h"

#include "HNKGameState.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API AHNKGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void Server_PlayerReadyUp(APlayerController* PlayerController);
	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void Server_PlayerUnreadyUp(APlayerController* PlayerController);
	
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<APlayerController*> ReadyPlayerControllers;
};
