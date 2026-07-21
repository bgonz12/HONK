// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/HNKCharacterMoverComponent.h"

void UHNKCharacterMoverComponent::OnRegister()
{
    UCharacterMoverComponent::OnRegister();
    
    RefreshSharedSettings();
}
