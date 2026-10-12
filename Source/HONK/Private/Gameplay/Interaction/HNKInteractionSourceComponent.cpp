// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Interaction/HNKInteractionSourceComponent.h"

// HONK Includes
#include "Gameplay/Interaction/HNKInteractableComponent.h"

// Engine Includes
#include "Components/WidgetComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/Interaction/HNKInteractPromptWidget.h"

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
		
		InitInteractPromptWidgetComponent();
		
		if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			Input->BindAction(InteractInputAction, ETriggerEvent::Started, this, &UHNKInteractionSourceComponent::Input_InteractStarted);
			Input->BindAction(InteractInputAction, ETriggerEvent::Completed, this, &UHNKInteractionSourceComponent::Input_InteractCompleted);
		}
	}
}

void UHNKInteractionSourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	EvaluateCurrentInteractable();
	
	if (HoldInteractTimerHandle.IsValid())
	{
		UpdateHoldInteract();
	}
}

void UHNKInteractionSourceComponent::AddInteractableComponent(UHNKInteractableComponent* InteractableComponent)
{
	InteractableComponents.Add(InteractableComponent);
}

void UHNKInteractionSourceComponent::RemoveInteractableComponent(UHNKInteractableComponent* InteractableComponent)
{
	InteractableComponents.Remove(InteractableComponent);
}

void UHNKInteractionSourceComponent::InitInteractPromptWidgetComponent()
{
	if (InteractPromptWidgetComponent)
	{
		return;
	}
	
	if (!InteractPromptWidgetClass)
	{
		return;
	}
	
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return;
	}
	
	InteractPromptWidgetComponent = Cast<UWidgetComponent>(OwnerActor->AddComponentByClass(UWidgetComponent::StaticClass(), true, FTransform::Identity, false));
	if (InteractPromptWidgetComponent)
	{
		InteractPromptWidgetComponent->SetWidgetClass(InteractPromptWidgetClass);
		InteractPromptWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		InteractPromptWidgetComponent->SetDrawSize(FVector2D(250.f, 30.f));
		
		InteractPromptWidget = Cast<UHNKInteractPromptWidget>(InteractPromptWidgetComponent->GetWidget());
		
		RefreshInteractPromptWidget();
	}
}

void UHNKInteractionSourceComponent::RefreshInteractPromptWidget()
{
	if (!InteractPromptWidgetComponent)
	{
		return;
	}
	
	if (CurrentInteractable)
	{
		InteractPromptWidgetComponent->SetWorldLocation(CurrentInteractable->GetComponentLocation());
		InteractPromptWidgetComponent->SetVisibility(true);
		
		if (InteractPromptWidget)
		{
			InteractPromptWidget->SetInteractProgress(0.f);
			InteractPromptWidget->UpdateInteractText(CurrentInteractable);
		}
	}
	else
	{
		InteractPromptWidgetComponent->SetVisibility(false);
	}
}

void UHNKInteractionSourceComponent::Input_InteractStarted(const FInputActionValue& Value)
{
	BeginInteract(CurrentInteractable);
}

void UHNKInteractionSourceComponent::Input_InteractCompleted(const FInputActionValue& Value)
{
	EndInteract(CurrentInteractable);
}

void UHNKInteractionSourceComponent::BeginInteract(UHNKInteractableComponent* InteractableComponent)
{
	if (!InteractableComponent)
	{
		return;
	}
	
	switch (InteractableComponent->GetInteractionType())
	{
	case EHNKInteractionType::IT_Press:
		TryTriggerInteract(InteractableComponent);
		break;
		
	case EHNKInteractionType::IT_Hold:
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimer(HoldInteractTimerHandle, this, &UHNKInteractionSourceComponent::FinishHoldInteract, 1.0, false, InteractableComponent->GetRequiredHoldDuration());
		}
		break;
		
	default:
		break;
	}
}

void UHNKInteractionSourceComponent::EndInteract(UHNKInteractableComponent* InteractableComponent)
{
	if (HoldInteractTimerHandle.IsValid())
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(HoldInteractTimerHandle);
			HoldInteractTimerHandle.Invalidate();
		}
	}
	
	RefreshInteractPromptWidget();
}

void UHNKInteractionSourceComponent::UpdateHoldInteract()
{
	if (!CurrentInteractable || !InteractPromptWidgetComponent)
	{
		return;
	}
	
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	const float HoldTimeElapsed = World->GetTimerManager().GetTimerElapsed(HoldInteractTimerHandle);
	const float RequiredHoldDuration = CurrentInteractable->GetRequiredHoldDuration();
	
	if (RequiredHoldDuration > 0.f)
	{
		InteractPromptWidget->SetInteractProgress(HoldTimeElapsed / RequiredHoldDuration);
	}
	else
	{
		InteractPromptWidget->SetInteractProgress(0.f);
	}
}

void UHNKInteractionSourceComponent::FinishHoldInteract()
{
	TryTriggerInteract(CurrentInteractable);
	EndInteract(CurrentInteractable);
}

void UHNKInteractionSourceComponent::TryTriggerInteract(UHNKInteractableComponent* InteractableComponent)
{
	if (!CanTriggerInteract(InteractableComponent))
	{
		return;
	}

	TriggerInteract(CurrentInteractable);

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
	
	EndInteract(CurrentInteractable);

	UHNKInteractableComponent* OldInteractable = CurrentInteractable;
	CurrentInteractable = InInteractableComponent;
	
	RefreshInteractPromptWidget();
	
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

