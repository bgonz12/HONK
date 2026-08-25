// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HNKGameMode.generated.h"

class APlayerController;

UCLASS()
class HONK_API AHNKGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	//~ Begin AGameModeBase Interface
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	//~ End AGameModeBase Interface
	
	//~ Begin AGameMode Interface
	virtual bool ReadyToStartMatch_Implementation() override;
	//~ End AGameMode Interface

	
	UFUNCTION(BlueprintCallable)
	void GetConnectedPlayerControllers(TArray<APlayerController*>& OutPlayerControllers) const;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleANywhere)
	TArray<APlayerController*> ConnectedPlayerControllers;
	
	bool bFinishedMapInitialLoad = false;
};
