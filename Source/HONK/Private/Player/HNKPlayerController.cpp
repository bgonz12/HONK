// HONK Includes
#include "Player/HNKPlayerController.h"
#include "Player/HNKPlayerState.h"

// Engine Includes
#include "AbilitySystemGlobals.h"
#include "Game/HNKGameState.h"
#include "Kismet/GameplayStatics.h"

UAbilitySystemComponent* AHNKPlayerController::GetAbilitySystemComponent() const
{
	if (APawn* MyPawn = GetPawn())
	{
		return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(MyPawn);
	}
	
	return nullptr;
}

void AHNKPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	
	bPlayerDependenciesReady = false;
	TryHandlePlayerDependenciesReady();
}

void AHNKPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	bPlayerDependenciesReady = false;
	TryHandlePlayerDependenciesReady();
}

void AHNKPlayerController::OnUnPossess()
{
	bPlayerDependenciesReady = false;
	
	Super::OnUnPossess();
}

void AHNKPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	
	bPlayerDependenciesReady = false;
	TryHandlePlayerDependenciesReady();
}

void AHNKPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	bPlayerDependenciesReady = false;
	TryHandlePlayerDependenciesReady();
}

void AHNKPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();
	
	BP_BeginPlayingState();
}

bool AHNKPlayerController::ArePlayerDependenciesReady()
{
	return bPlayerDependenciesReady;
}

void AHNKPlayerController::TryHandlePlayerDependenciesReady()
{
	if (bPlayerDependenciesReady)
	{
		return;
	}
	
	AHNKPlayerState* MyPlayerState = GetPlayerState<AHNKPlayerState>();
	if (!IsValid(MyPlayerState))
	{
		return;
	}
	
	APawn* MyPawn = GetPawn();
	if (!IsValid(MyPawn))
	{
		return;
	}
	
	bPlayerDependenciesReady = true;
	
	HandlePlayerDependenciesReady();
}

void AHNKPlayerController::HandlePlayerDependenciesReady()
{
	BP_HandlePlayerDependenciesReady();
	
	OnPlayerDependenciesReady.Broadcast(this);
}

void AHNKPlayerController::Server_ReadyUp_Implementation()
{
	if (AHNKGameState* GameState = Cast<AHNKGameState>(UGameplayStatics::GetGameState(this)))
	{
		GameState->Server_PlayerReadyUp(this);
	}
}
