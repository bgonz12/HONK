// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Interaction/HNKInteractionSourceComponent.h"

// HONK Includes
#include "EnhancedInputComponent.h"
#include "Gameplay/Interaction/HNKInteractableComponent.h"

UHNKInteractionSourceComponent::UHNKInteractionSourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	UHNKInteractionSourceComponent::SetComponentTickEnabled(false);
}

void UHNKInteractionSourceComponent::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* OwnerPawn = GetOwner<APawn>();
	if (!OwnerPawn)
	{
		return;
	}
	
	APlayerController* PlayerController = OwnerPawn->GetController<APlayerController>();
	if (!PlayerController)
	{
		return;
	}
	
	if (OwnerPawn->IsLocallyControlled())
	{
		SetComponentTickEnabled(true);
		
		if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			Input->BindAction(InteractInputAction, ETriggerEvent::Started, this, &UHNKInteractionSourceComponent::Input_Interact);
		}
	}
}

void UHNKInteractionSourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	EvaluateCurrentInteractable();
}

void UHNKInteractionSourceComponent::AddInteractableComonent(UHNKInteractableComponent* InteractableComponent)
{
	InteractableComponents.Add(InteractableComponent);
}

void UHNKInteractionSourceComponent::RemoveInteractableComonent(UHNKInteractableComponent* InteractableComponent)
{
	InteractableComponents.Remove(InteractableComponent);
}

void UHNKInteractionSourceComponent::Input_Interact(const FInputActionValue& Value)
{
	TryTriggerInteract(CurrentInteractable);

	if (APawn* OwnerPawn = GetOwner<APawn>())
	{
		if (!OwnerPawn->HasAuthority())
		{
			ServerTryTriggerInteract(CurrentInteractable);
		}
	}
}

void UHNKInteractionSourceComponent::ServerTryTriggerInteract_Implementation(UHNKInteractableComponent* InteractableComponent)
{
	TryTriggerInteract(InteractableComponent);
}

void UHNKInteractionSourceComponent::TryTriggerInteract(UHNKInteractableComponent* InteractableComponent)
{
	if (!CanTriggerInteract(InteractableComponent))
	{
		return;
	}
	
	TriggerInteract(InteractableComponent);
}

void UHNKInteractionSourceComponent::TriggerInteract(UHNKInteractableComponent* InteractableComponent)
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return;
	}
	
	InteractableComponent->TriggerInteract(OwnerActor, OwnerActor->HasAuthority());
}

bool UHNKInteractionSourceComponent::CanTriggerInteract(UHNKInteractableComponent* InteractableComponent)
{
	if (!IsValid(InteractableComponent))
	{
		return false;
	}
	
	return true;
}

void UHNKInteractionSourceComponent::SetCurrentInteractableComponent(UHNKInteractableComponent* InInteractableComponent)
{
	if (CurrentInteractable == InInteractableComponent)
	{
		return;
	}
	
	UHNKInteractableComponent* OldInteractable = CurrentInteractable;
	CurrentInteractable = InInteractableComponent;
	
	OnCurrentInteractableChanged.Broadcast(this, OldInteractable, CurrentInteractable);
}

void UHNKInteractionSourceComponent::EvaluateCurrentInteractable()
{
	APawn* OwnerPawn = GetOwner<APawn>();
	if (!IsValid(OwnerPawn))
	{
		SetCurrentInteractableComponent(nullptr);
		return;
	}
	
	AController* Controller = OwnerPawn->GetController();
	if (!IsValid(Controller))
	{
		SetCurrentInteractableComponent(nullptr);
		return;
	}
	
	UHNKInteractableComponent* BestInteractable = nullptr;
	float BestDot = -MAX_flt;
	
	const FVector OwnerLocation = OwnerPawn->GetActorLocation();
	const FVector ControlForwardDir =  Controller->GetControlRotation().Vector();
	for (UHNKInteractableComponent* Interactable : InteractableComponents)
	{
		if (!IsValid(Interactable))
		{
			continue;
		}
		
		const FVector InteractableDir = (Interactable->GetComponentLocation() - OwnerLocation).GetSafeNormal2D();
		
		const float CandidateDot = FVector::DotProduct(ControlForwardDir, InteractableDir);
		if (CandidateDot > BestDot)
		{
			BestInteractable = Interactable;
			BestDot = CandidateDot;
		}
	}
	
	SetCurrentInteractableComponent(BestInteractable);
}

