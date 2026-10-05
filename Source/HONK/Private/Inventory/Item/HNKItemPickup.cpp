// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/HNKItemPickup.h"

#include "Gameplay/Interaction/HNKInteractableComponent.h"

AHNKItemPickup::AHNKItemPickup()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);
	
	InteractableComponent = CreateDefaultSubobject<UHNKInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(RootComponent);
}
