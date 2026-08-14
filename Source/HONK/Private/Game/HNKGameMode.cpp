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

void AHNKGameMode::GetConnectedPlayerControllers(TArray<APlayerController*>& OutPlayerControllers) const
{
	OutPlayerControllers = ConnectedPlayerControllers;
}
