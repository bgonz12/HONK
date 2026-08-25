// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/HNKGameMode.h"

// Engine Includes
#include "Gameframework/PlayerController.h"

void AHNKGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	ConnectedPlayerControllers.AddUnique(NewPlayer);
}

void AHNKGameMode::Logout(AController* Exiting)
{
	if (APlayerController* ExitingPlayer = Cast<APlayerController>(Exiting))
	{
		ConnectedPlayerControllers.Remove(ExitingPlayer);
	}
	
	Super::Logout(Exiting);
}

bool AHNKGameMode::ReadyToStartMatch_Implementation()
{
	// Waiting a frame so we can get the player starts
	if (!bFinishedMapInitialLoad)
	{
		bFinishedMapInitialLoad = true;
		return false;
	}
	
	return Super::ReadyToStartMatch_Implementation();
}

void AHNKGameMode::GetConnectedPlayerControllers(TArray<APlayerController*>& OutPlayerControllers) const
{
	OutPlayerControllers = ConnectedPlayerControllers;
}
