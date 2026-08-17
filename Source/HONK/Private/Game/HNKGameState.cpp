// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/HNKGameState.h"

// HONK Includes
#include "Game/HNKGameMode.h"
#include "Kismet/GameplayStatics.h"

void AHNKGameState::Server_PlayerReadyUp_Implementation(APlayerController* PlayerController)
{
	if (!ReadyPlayerControllers.Contains(PlayerController))
	{
		ReadyPlayerControllers.AddUnique(PlayerController);
	}
}

void AHNKGameState::Server_PlayerUnreadyUp_Implementation(APlayerController* PlayerController)
{
	if (ReadyPlayerControllers.Contains(PlayerController))
	{
		ReadyPlayerControllers.Remove(PlayerController);
	}
}