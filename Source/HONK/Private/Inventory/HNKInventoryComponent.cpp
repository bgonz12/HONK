// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/HNKInventoryComponent.h"

// HONK Includes
#include "Inventory/Item/HNKItemDefinition.h"
#include "Inventory/Item/HNKItemDrop.h"
#include "Inventory/Item/Fragment/HNKItemFragment_WorldRepresentation.h"

// Engine Includes
#include "Inventory/HNKInventoryStatics.h"
#include "Inventory/Item/Fragment/HNKItemFragment_Stackable.h"
#include "Net/UnrealNetwork.h"

UHNKInventoryComponent::UHNKInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(true);
}

void UHNKInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UHNKInventoryComponent, Items);
}

bool UHNKInventoryComponent::AddItem(FHNKItemStack& InOutNewItem)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner || !MyOwner->HasAuthority())
	{
		return false;
	}
	
	if (!IsValid(InOutNewItem.ItemDef))
	{
		return false;
	}
	
	// Fill out existing ItemStacks with empty space
	const int32 MaxItemStackCount = UHNKInventoryStatics::GetMaxStackCount(InOutNewItem.ItemDef);
	if (MaxItemStackCount <= 0)
	{
		return false;
	}
	
	while (InOutNewItem.Count > 0)
	{
		int32 ItemWithEmptySpaceIndex = FindStackWithEmptySpace(InOutNewItem.ItemDef);
		if (ItemWithEmptySpaceIndex >= 0)
		{
			const int32 CountToAdd = FMath::Min(MaxItemStackCount - Items[ItemWithEmptySpaceIndex].Count, InOutNewItem.Count);
	
			Items[ItemWithEmptySpaceIndex].Count += CountToAdd;
			InOutNewItem.Count -= CountToAdd;
		}
		else
		{
			const int32 CountToAdd = FMath::Min(MaxItemStackCount, InOutNewItem.Count);

			FHNKItemStack CurrentItemStack;
			CurrentItemStack.ItemDef = InOutNewItem.ItemDef;
			CurrentItemStack.Count = CountToAdd;
			InOutNewItem.Count -= CountToAdd;
		
			Items.Add(CurrentItemStack);
		}
	}
	
	OnRep_Items();
	return true;
}

bool UHNKInventoryComponent::RemoveItem(int32 ItemIndex)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner || !MyOwner->HasAuthority())
	{
		return false;
	}
	
	if (Items.IsValidIndex(ItemIndex))
	{
		Items.RemoveAt(ItemIndex);
		OnRep_Items();
		return true;
	}
	
	return false;
}

bool UHNKInventoryComponent::DropItem(int32 ItemIndex)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner || !MyOwner->HasAuthority())
	{
		return false;
	}
	
	if (!Items.IsValidIndex(ItemIndex))
	{
		return false;
	}
	
	const UHNKItemFragment_WorldRepresentation* Fragment = Cast<UHNKItemFragment_WorldRepresentation>(UHNKItemDefinition::FindFragmentByClass(Items[ItemIndex].ItemDef, UHNKItemFragment_WorldRepresentation::StaticClass()));
	if (!Fragment || !Fragment->bCanBeDropped || !Fragment->ItemDropClass)
	{
		return false;
	}
		
	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}
	
	FTransform DropTransform;
	if (!GetDropTransform(DropTransform))
	{
		return false;
	}
	
	AHNKItemDrop* ItemDrop = World->SpawnActor<AHNKItemDrop>(Fragment->ItemDropClass, DropTransform);
	ItemDrop->SetItemStack(Items[ItemIndex]);

	RemoveItem(ItemIndex);
	return true;
}

void UHNKInventoryComponent::OnRep_Items()
{
	OnInventoryChanged.Broadcast(this);
}

int32 UHNKInventoryComponent::FindStackWithEmptySpace(TSubclassOf<UHNKItemDefinition> ItemDef) const
{
	if (!IsValid(ItemDef))
	{
		return -1;
	}
	
	const int32 MaxItemStackCount = UHNKInventoryStatics::GetMaxStackCount(ItemDef);
	if (MaxItemStackCount <= 1)
	{
		return -1;
	}
	
	for (int32 I = 0; I < Items.Num(); ++I)
	{
		const FHNKItemStack& ItemStack = Items[I];
		
		if (ItemStack.ItemDef == ItemDef)
		{
			if (ItemStack.Count < MaxItemStackCount)
			{
				return I;
			}
		}
	}
	
	return -1;
}

bool UHNKInventoryComponent::GetDropTransform(FTransform& OutTransform) const
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return false;
	}
	
	OutTransform.SetLocation(MyOwner->GetActorLocation() + MyOwner->GetActorForwardVector() * 200.f);
	OutTransform.SetRotation(MyOwner->GetActorRotation().Quaternion());
	return true;
}

