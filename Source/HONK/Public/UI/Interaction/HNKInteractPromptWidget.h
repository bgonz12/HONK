// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "HNKInteractPromptWidget.generated.h"

class UProgressBar;
class UTextBlock;
enum class EHNKInteractionType : uint8;

/**
 * 
 */
UCLASS()
class HONK_API UHNKInteractPromptWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	//~Begin UUserWidget
	virtual void NativePreConstruct() override;
	//~End UUserWidget
	
	UFUNCTION(BlueprintCallable)
	void UpdateInteractText(UHNKInteractableComponent* InteractableComponent);
	
	UFUNCTION(BlueprintCallable)
	void SetInteractProgress(float InPercent);
	
protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Interact_TextBlock;
	
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UProgressBar> Interact_ProgressBar;
	
	UPROPERTY(BlueprintReadOnly)
	EHNKInteractionType InteractionType;
};
