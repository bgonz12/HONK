// HONK Includes
#include "Player/HKPlayerController.h"


void AHKPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();
	BP_BeginPlayingState();
}

void AHKPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	BP_OnRep_Pawn();

	OnRep_Pawn_Delegate.Broadcast(this);
}


void AHKPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	BP_OnRep_PlayerState();
}
