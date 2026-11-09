#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerController.h"

// HONK Includes
#include "HNKPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHNKPlayerDependenciesReady, const AHNKPlayerController*, HNKPlayerController);

UCLASS()
class HONK_API AHNKPlayerController : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	//~Begin AController
	virtual void InitPlayerState() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void OnRep_Pawn() override;
	virtual void OnRep_PlayerState() override;
	//~End AController
	
	//~Begin APlayerController
	virtual void BeginPlayingState() override;
	//~End APlayerController
	
	//~Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End IAbilitySystemInterface
	
	UFUNCTION(BlueprintImplementableEvent, Category = "HNKPlayerController")
	void BP_BeginPlayingState();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "HNKPlayerController")
	void BP_HandlePlayerDependenciesReady();
	
	UFUNCTION(BlueprintPure)
	bool ArePlayerDependenciesReady();
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "HNKPlayerController|Pawn")
	void Server_ReadyUp();
	
protected:
	virtual void TryHandlePlayerDependenciesReady();
	
	virtual void HandlePlayerDependenciesReady();
	
public:
	UPROPERTY(BlueprintAssignable)
	FHNKPlayerDependenciesReady OnPlayerDependenciesReady;
	
protected:
	bool bPlayerDependenciesReady = false;
};
