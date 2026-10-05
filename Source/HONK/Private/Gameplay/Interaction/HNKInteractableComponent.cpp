// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Interaction/HNKInteractableComponent.h"

// HONK Includes
#include "Gameplay/Interaction/HNKInteractionSourceComponent.h"
#include "Gameplay/Interaction/HNKInteractionSourceInterface.h"

UHNKInteractableComponent::UHNKInteractableComponent()
{
	InitSphereRadius(200.f);
}

void UHNKInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OnComponentBeginOverlap.AddDynamic(this, &UHNKInteractableComponent::ComponentBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UHNKInteractableComponent::ComponentEndOverlap);
}

void UHNKInteractableComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnComponentBeginOverlap.RemoveDynamic(this, &UHNKInteractableComponent::ComponentBeginOverlap);
	OnComponentEndOverlap.RemoveDynamic(this, &UHNKInteractableComponent::ComponentEndOverlap);
	
	Super::EndPlay(EndPlayReason);
}

void UHNKInteractableComponent::TriggerInteract(AActor* InteractingActor, bool bIsServerInteract)
{
	OnInteractableTriggered.Broadcast(InteractingActor, bIsServerInteract);
}

void UHNKInteractableComponent::GetInteractionText(FText& OutInteractionText)
{
	OutInteractionText = InteractionText;
}

void UHNKInteractableComponent::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IHNKInteractionSourceInterface* InteractionSource = Cast<IHNKInteractionSourceInterface>(OtherActor))
	{
		if (UHNKInteractionSourceComponent* ISC = InteractionSource->GetInteractionSourceComponent())
		{
			ISC->AddInteractableComonent(this);
		}
	}
}

void UHNKInteractableComponent::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IHNKInteractionSourceInterface* InteractionSource = Cast<IHNKInteractionSourceInterface>(OtherActor))
	{
		if (UHNKInteractionSourceComponent* ISC = InteractionSource->GetInteractionSourceComponent())
		{
			ISC->RemoveInteractableComonent(this);
		}
	}
}
