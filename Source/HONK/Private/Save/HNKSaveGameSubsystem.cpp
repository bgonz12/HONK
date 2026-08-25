// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/HNKSaveGameSubsystem.h"

// HONK Includes
#include "Save/HNKSaveableObjectInterface.h"
#include "Save/HNKSaveGame_Player.h"
#include "Save/HNKSaveGame_Session.h"

// Engine Includes
#include "Kismet/GameplayStatics.h"

void UHNKSaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (!TryLoadingDataFromDisk(EHNKSaveType::ST_Player))
	{
		CreateNewSaveGame(EHNKSaveType::ST_Player);
	}
	
	if (!TryLoadingDataFromDisk(EHNKSaveType::ST_Session))
	{
		CreateNewSaveGame(EHNKSaveType::ST_Session);
	}
}

bool UHNKSaveGameSubsystem::TrySavingDataToDisk(EHNKSaveType SaveType)
{
	switch (SaveType)
	{
	case EHNKSaveType::ST_Player:
		if (PlayerSaveGameInstance)
		{
			return UGameplayStatics::SaveGameToSlot(PlayerSaveGameInstance, TEXT("PlayerSlot1"), 0);
		}
		break;
		
	case EHNKSaveType::ST_Session:
		if (SessionSaveGameInstance)
		{
			return UGameplayStatics::SaveGameToSlot(SessionSaveGameInstance, TEXT("SessionSlot1"), 0);
		}
		break;
		
	default:
		break;
	}
	
	return false;
}

bool UHNKSaveGameSubsystem::TryLoadingDataFromDisk(EHNKSaveType SaveType)
{
	switch (SaveType)
	{
	case EHNKSaveType::ST_Player:
		PlayerSaveGameInstance = Cast<UHNKSaveGame_Player>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSlot1"), 0));
		return IsValid(PlayerSaveGameInstance);
		
	case EHNKSaveType::ST_Session:
		SessionSaveGameInstance = Cast<UHNKSaveGame_Session>(UGameplayStatics::LoadGameFromSlot(TEXT("SessionSlot1"), 0));
		return IsValid(SessionSaveGameInstance);
		
	default:
		break;
	}
	
	return false;
}

void UHNKSaveGameSubsystem::CreateNewSaveGame(EHNKSaveType SaveType)
{
	switch (SaveType)
	{
	case EHNKSaveType::ST_Player:
		PlayerSaveGameInstance = Cast<UHNKSaveGame_Player>(UGameplayStatics::CreateSaveGameObject(UHNKSaveGame_Player::StaticClass()));
		break;
		
	case EHNKSaveType::ST_Session:
		SessionSaveGameInstance = Cast<UHNKSaveGame_Session>(UGameplayStatics::CreateSaveGameObject(UHNKSaveGame_Session::StaticClass()));
		break;
		
	default:
		break;
	}
}

UHNKSaveGame* UHNKSaveGameSubsystem::GetSaveGameInstance(EHNKSaveType SaveType) const
{
	switch (SaveType)
	{
	case EHNKSaveType::ST_Player:
		return PlayerSaveGameInstance;
		
	case EHNKSaveType::ST_Session:
		return SessionSaveGameInstance;
		
	default:
		break;
	}
	
	return nullptr;
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
