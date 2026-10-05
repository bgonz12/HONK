// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HNKInteractionSourceComponent.generated.h"

class UHNKInteractableComponent;
class UInputAction;
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
	
	void AddInteractableComonent(UHNKInteractableComponent* InteractableComponent);
	void RemoveInteractableComonent(UHNKInteractableComponent* InteractableComponent);
	
protected:
	void Input_Interact(const FInputActionValue& Value);
	
	UFUNCTION(Server, Reliable)
	void ServerTryTriggerInteract(UHNKInteractableComponent* InteractableComponent);
	
	void TryTriggerInteract(UHNKInteractableComponent* InteractableComponent);
	
	void TriggerInteract(UHNKInteractableComponent* InteractableComponent);
	
	bool CanTriggerInteract(UHNKInteractableComponent* InteractableComponent);
	
	void SetCurrentInteractableComponent(UHNKInteractableComponent* InInteractableComponent);
	
	void EvaluateCurrentInteractable();
	
public:
	UPROPERTY(BlueprintAssignable)
	FHNKInteractableChanged OnCurrentInteractableChanged;
	
protected:
	UPROPERTY()
	TArray<UHNKInteractableComponent*> InteractableComponents;
	
	UPROPERTY()
	UHNKInteractableComponent* CurrentInteractable;
	
	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> InteractInputAction;
};
