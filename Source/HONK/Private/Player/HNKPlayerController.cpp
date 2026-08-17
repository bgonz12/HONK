// HONK Includes
#include "Player/HNKPlayerController.h"
#include "Player/HNKPlayerStateBase.h"

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

void AHNKPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();
	BP_BeginPlayingState();
}

void AHNKPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	BP_OnRep_Pawn();

	OnRep_Pawn_Delegate.Broadcast(this, GetPawn());
}

void AHNKPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	BP_OnRep_PlayerState();
}

void AHNKPlayerController::Server_ReadyUp_Implementation()
{
	if (AHNKGameState* GameState = Cast<AHNKGameState>(UGameplayStatics::GetGameState(this)))
	{
		GameState->Server_PlayerReadyUp(this);
	}
}
