#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerController.h"

// HONK Includes
#include "HNKPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHNK_OnRep_Pawn_Signature, const AHNKPlayerController*, HNKPlayerController, const APawn*, Pawn);

UCLASS()
class HONK_API AHNKPlayerController : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	/** IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void BeginPlayingState() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "HNKPlayerController")
	void BP_BeginPlayingState();

	virtual void OnRep_Pawn() override;
	UFUNCTION(BlueprintImplementableEvent, Category = "HNKPlayerController|Pawn")
	void BP_OnRep_Pawn();

	virtual void OnRep_PlayerState() override;
	UFUNCTION(BlueprintImplementableEvent, Category = "HNKPlayerController|Pawn")
	void BP_OnRep_PlayerState();

public:
	UPROPERTY(BlueprintAssignable)
	FHNK_OnRep_Pawn_Signature OnRep_Pawn_Delegate;
};
