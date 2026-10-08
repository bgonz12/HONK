// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HNKInteractionSourceComponent.generated.h"

class UHNKInteractableComponent;
class UHNKInteractPromptWidget;
class UInputAction;
class UUserWidget;
class UWidgetComponent;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHNKInteractableChanged, UHNKInteractionSourceComponent*, InteractionSourceComponent, UHNKInteractableComponent*, OldInteractable, UHNKInteractableComponent*, NewInteractable);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HONK_API UHNKInteractionSourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHNKInteractionSourceComponent();

	//~Begin UActorComponent
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//~End UActorComponent
	
	void AddInteractableComponent(UHNKInteractableComponent* InteractableComponent);
	void RemoveInteractableComponent(UHNKInteractableComponent* InteractableComponent);
	
protected:
	void InitInteractPromptWidgetComponent();
	
	void RefreshInteractPromptWidget();
	
	void Input_InteractStarted(const FInputActionValue& Value);
	
	void Input_InteractCompleted(const FInputActionValue& Value);

	void BeginInteract(UHNKInteractableComponent* InteractableComponent);
	void EndInteract(UHNKInteractableComponent* InteractableComponent);

	void UpdateHoldInteract();
	void FinishHoldInteract();

	void TryTriggerInteract(UHNKInteractableComponent* InteractableComponent);
	
	UFUNCTION(Server, Reliable)
	void ServerTryTriggerInteract(UHNKInteractableComponent* InteractableComponent);
	
	void TriggerInteract(UHNKInteractableComponent* InteractableComponent);
	
	bool CanTriggerInteract(UHNKInteractableComponent* InteractableComponent);
	
	void SetCurrentInteractableComponent(UHNKInteractableComponent* InInteractableComponent);
	
	void EvaluateCurrentInteractable();
	
	
public:
	UPROPERTY(BlueprintAssignable)
	FHNKInteractableChanged OnCurrentInteractableChanged;
	
protected:
	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> InteractInputAction;
	
	UPROPERTY(Transient)
	TArray<UHNKInteractableComponent*> InteractableComponents;
	
	UPROPERTY(Transient)
	UHNKInteractableComponent* CurrentInteractable;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHNKInteractPromptWidget> InteractPromptWidgetClass;
	
	UPROPERTY(Transient)
	TObjectPtr<UHNKInteractPromptWidget> InteractPromptWidget;
	
	UPROPERTY(Transient)
	TObjectPtr<UWidgetComponent> InteractPromptWidgetComponent;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	FTimerHandle HoldInteractTimerHandle;
};
