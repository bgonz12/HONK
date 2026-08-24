// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Escape/HNKGameState_Escape.h"

// HONK Includes
#include "Game/Escape/HNKGameMode_Escape.h"

// Engine Includes
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Save/HNKSaveGame_Session.h"

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

void AHNKGameState_Escape::Server_PlayerReadyUp(APlayerController* PlayerController)
{
	Super::Server_PlayerReadyUp(PlayerController);
	
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

void AHNKGameState_Escape::Server_PlayerUnreadyUp(APlayerController* PlayerController)
{
	Super::Server_PlayerUnreadyUp(PlayerController);
}

void AHNKGameState_Escape::SaveObject(USaveGame* SaveGame)
{
	if (UHNKSaveGame_Session* SessionSave = Cast<UHNKSaveGame_Session>(SaveGame))
	{
		SessionSave->CurrentDay = CurrentDay;
		SessionSave->CurrentMoney = CurrentMoney;
	}
}

void AHNKGameState_Escape::LoadObject(USaveGame* SaveGame)
{
	if (UHNKSaveGame_Session* SessionSave = Cast<UHNKSaveGame_Session>(SaveGame))
	{
		CurrentDay = SessionSave->CurrentDay;
		CurrentMoney = SessionSave->CurrentMoney;
	}
}

void AHNKGameState_Escape::SetCurrentEscapeState(const EHNKEscapeState& InEscapeState)
{
	if (InEscapeState == CurrentEscapeState)
	{
		return;
	}
	
	EHNKEscapeState OldEscapeState = CurrentEscapeState;
	CurrentEscapeState = InEscapeState;
	
	BP_CurrentEscapeStateChanged(CurrentEscapeState);
	OnEscapeStateChanged.Broadcast(this, CurrentEscapeState);
}
