// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Equipment/HNKEquipmentInstance.h"

// HONK Includes
#include "GAS/Abilities/HNKGameplayAbilitySet.h"
#include "Inventory/Equipment/HNKEquipmentAttachment.h"
#include "Inventory/Equipment/HNKEquipmentDefinition.h"
#include "Inventory/Item/HNKItemInstance.h"
#include "Inventory/ItemFragment/HNKItemFragment_Equippable.h"
#include "Player/HNKPlayerCharacter.h"

// Engine Includes
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

void UHNKEquipmentInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UHNKEquipmentInstance, EquipmentDef);
	DOREPLIFETIME(UHNKEquipmentInstance, AttachmentActor);
}

bool UHNKEquipmentInstance::IsSupportedForNetworking() const
{
	return true;
}

void UHNKEquipmentInstance::Initialize(UHNKItemInstance* ItemInstance, ACharacter* Character)
{
	if (!ItemInstance)
	{
		return;
	}
	
	SourceItemInstance = ItemInstance;
	
	const UHNKItemFragment_Equippable* EquippableFragment = Cast<UHNKItemFragment_Equippable>(ItemInstance->FindFragmentByClass(UHNKItemFragment_Equippable::StaticClass()));
	if (!EquippableFragment)
	{
		return;
	}
	
	EquipmentDef = EquippableFragment->EquipmentDef;
	
	HandleEquipItem(Character);
}

void UHNKEquipmentInstance::HandleEquipItem(ACharacter* Character)
{
	UHNKEquipmentDefinition* EquipmentDefCDO = EquipmentDef.GetDefaultObject();
	if (!EquipmentDefCDO || !EquipmentDefCDO->EquipmentAttachmentClass)
	{
		return;
	}
	
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	AttachmentActor = World->SpawnActor<AHNKEquipmentAttachment>(EquipmentDefCDO->EquipmentAttachmentClass);
	if (!AttachmentActor)
	{
		return;
	}
	
	AttachmentActor->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, EquipmentDefCDO->AttachSocketName);
	
	if (EquipmentDefCDO->AnimationOverrides.IsValid())
	{
		if (AHNKPlayerCharacter* PlayerCharacter = Cast<AHNKPlayerCharacter>(Character))
		{
			PlayerCharacter->SetAnimationOverrides(EquipmentDefCDO->AnimationOverrides);
		}
	}
	
	// Apply gameplay effects
	
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Character))
	{
		if (UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent())
		{
			if (EquipmentDefCDO->AbilitySet)
			{
				EquipmentDefCDO->AbilitySet->GiveAbilities(ASC);
			}
		}
	}
}

void UHNKEquipmentInstance::HandleUnequipItem(ACharacter* Character)
{
	if (AttachmentActor)
	{
		AttachmentActor->Destroy();
		AttachmentActor = nullptr;
	}
	
	UHNKEquipmentDefinition* EquipmentDefCDO = EquipmentDef.GetDefaultObject();
	if (!EquipmentDefCDO || !EquipmentDefCDO->EquipmentAttachmentClass)
	{
		return;
	}
	
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Character))
	{
		if (UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent())
		{
			if (EquipmentDefCDO->AbilitySet)
			{
				EquipmentDefCDO->AbilitySet->ClearAbilities(ASC);
			}
		}
	}
	
	// Remove gameplay effects
	
	if (AHNKPlayerCharacter* PlayerCharacter = Cast<AHNKPlayerCharacter>(Character))
	{
		PlayerCharacter->ClearAnimationOverrides();
	}
}
