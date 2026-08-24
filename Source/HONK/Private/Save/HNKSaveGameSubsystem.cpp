// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/HNKSaveGameSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Save/HNKSaveableObjectInterface.h"
#include "Save/HNKSaveGame_Session.h"

void UHNKSaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (!TryLoadSession())
	{
		CreateNewSessionSaveGame();
	}
}

bool UHNKSaveGameSubsystem::TryLoadSession()
{
	SessionSaveGameInstance = Cast<UHNKSaveGame_Session>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));
	
	return IsValid(SessionSaveGameInstance);
}

bool UHNKSaveGameSubsystem::SaveSession()
{
	if (!SessionSaveGameInstance)
	{
		return false;
	}
	
	return UGameplayStatics::SaveGameToSlot(SessionSaveGameInstance, TEXT("Slot1"), 0);
}

void UHNKSaveGameSubsystem::CreateNewSessionSaveGame()
{
	SessionSaveGameInstance = Cast<UHNKSaveGame_Session>(UGameplayStatics::CreateSaveGameObject(UHNKSaveGame_Session::StaticClass()));
}

UHNKSaveGame_Session* UHNKSaveGameSubsystem::GetSessionSaveGameInstance() const
{
	return SessionSaveGameInstance;
}

void UHNKSaveGameSubsystem::SaveObject(UObject* Object)
{
	if (!SessionSaveGameInstance)
	{
		return;
	}
	
	if (IHNKSaveableObjectInterface* SavableObject = Cast<IHNKSaveableObjectInterface>(Object))
	{
		SavableObject->SaveObject(SessionSaveGameInstance);
	}
}

void UHNKSaveGameSubsystem::LoadObject(UObject* Object)
{
	if (!SessionSaveGameInstance)
	{
		return;
	}
	
	if (IHNKSaveableObjectInterface* SavableObject = Cast<IHNKSaveableObjectInterface>(Object))
	{
		SavableObject->LoadObject(SessionSaveGameInstance);
	}
}
