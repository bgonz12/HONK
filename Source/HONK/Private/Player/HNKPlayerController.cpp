// HONK Includes
#include "Player/HNKPlayerController.h"

#include "AbilitySystemComponent.h"
#include "Player/HNKPlayerStateBase.h"

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
	
	if (AHNKPlayerStateBase* MyPlayerState = GetPlayerState<AHNKPlayerStateBase>())
	{
		if (UAbilitySystemComponent* MyASC = MyPlayerState->GetAbilitySystemComponent())
		{
			MyASC->InitAbilityActorInfo(MyPlayerState, GetPawn());
		}
	}
}
