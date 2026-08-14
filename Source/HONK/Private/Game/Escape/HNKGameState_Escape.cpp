// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Escape/HNKGameState_Escape.h"

// HONK Includes
#include "Game/Escape/HNKGameMode_Escape.h"

// Engine Includes
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void AHNKGameState_Escape::Server_PlayerReadyUp_Implementation(APlayerController* PlayerController)
{
	if (!ReadyPlayerControllers.Contains(PlayerController))
	{
		ReadyPlayerControllers.AddUnique(PlayerController);
		
		if (AHNKGameMode* GameMode = Cast<AHNKGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			TArray<APlayerController*> PlayerControllers;
			GameMode->GetConnectedPlayerControllers(PlayerControllers);
			
			if (ReadyPlayerControllers.Num() >= PlayerControllers.Num())
			{
				SetCurrentEscapeState(EHNKEscapeState::ES_Performance); // Begin Performance
			}
		}
	}
}

void AHNKGameState_Escape::Server_PlayerUnreadyUp_Implementation(APlayerController* PlayerController)
{
	if (ReadyPlayerControllers.Contains(PlayerController))
	{
		ReadyPlayerControllers.Remove(PlayerController);
	}
}

void AHNKGameState_Escape::SetTimeRemaining(float InTimeRemaining)
{
	TimeRemaining = InTimeRemaining;
}

void AHNKGameState_Escape::OnRep_CurrentEscapeState()
{
	OnEscapeStateChanged.Broadcast(this, CurrentEscapeState);
}

void AHNKGameState_Escape::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AHNKGameState_Escape, CurrentEscapeState);
}

void AHNKGameState_Escape::SetCurrentEscapeState(const EHNKEscapeState& InEscapeState)
{
	EHNKEscapeState OldEscapeState = CurrentEscapeState;
	CurrentEscapeState = InEscapeState;
	
	OnEscapeStateChanged.Broadcast(this, CurrentEscapeState);
}
