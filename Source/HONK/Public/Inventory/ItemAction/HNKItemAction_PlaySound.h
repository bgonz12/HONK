// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// HONK Includes
#include "HNKItemAction.h"
#include "HNKItemAction_PlaySound.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UHNKItemAction_PlaySound : public UHNKItemAction
{
	GENERATED_BODY()
	
public:
	virtual bool Execute(AActor* ItemOwner, UHNKItemInstance* ItemInstance) override;
	
protected:
	UPROPERTY(EditAnywhere)
	USoundBase* Sound;
};
