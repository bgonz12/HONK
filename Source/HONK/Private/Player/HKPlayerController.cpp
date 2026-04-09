// HONK Includes
#include "Player/HKPlayerController.h"

void AHKPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	BP_OnRep_Pawn();

	OnRep_Pawn_Delegate.Broadcast(this);
}
