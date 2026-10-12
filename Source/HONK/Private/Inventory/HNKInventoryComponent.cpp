// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/HNKInventoryComponent.h"

// HONK Includes
#include "Inventory/HNKInventoryStatics.h"
#include "Inventory/ItemFragment/HNKItemFragment_Useable.h"
#include "Inventory/ItemFragment/HNKItemFragment_WorldRepresentation.h"
#include "Inventory/Item/HNKItemDefinition.h"
#include "Inventory/Item/HNKItemDrop.h"
#include "Inventory/Item/HNKItemInstance.h"

// Engine Includes
#include "Inventory/Equipment/HNKEquipmentComponent.h"
#include "Inventory/Equipment/HNKEquipmentComponentInterface.h"
#include "Inventory/Equipment/HNKEquipmentInstance.h"
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

int32 UHNKInventoryComponent::AddItem(const FHNKItemDefinitionStack& InItemDefStack)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner || !MyOwner->HasAuthority())
	{
		return -1;
	}
	
	if (!IsValid(InItemDefStack.ItemDef))
	{
		return -1;
	}
	
	// Fill out existing ItemStacks with empty space
	const int32 MaxItemStackCount = UHNKInventoryStatics::GetMaxStackCount(InItemDefStack.ItemDef);
	if (MaxItemStackCount <= 0)
	{
		return -1;
	}
	
	int32 LastAddedItemIndex = -1;
	
	int32 RemainingCountToAdd = InItemDefStack.Count;
	while (RemainingCountToAdd > 0)
	{
		int32 ItemWithEmptySpaceIndex = FindStackWithEmptySpace(InItemDefStack.ItemDef);
		if (ItemWithEmptySpaceIndex >= 0)
		{
			const int32 CountToAdd = FMath::Min(MaxItemStackCount - Items[ItemWithEmptySpaceIndex].Count, RemainingCountToAdd);
	
			Items[ItemWithEmptySpaceIndex].Count += CountToAdd;
			RemainingCountToAdd -= CountToAdd;
			
			LastAddedItemIndex = ItemWithEmptySpaceIndex;
		}
		else
		{
			const int32 CountToAdd = FMath::Min(MaxItemStackCount, RemainingCountToAdd);
			
			UHNKItemInstance* ItemInstance = NewObject<UHNKItemInstance>(this);
			if (!ensure(ItemInstance))
			{
				return false;
			}
			
			ItemInstance->Initialize(InItemDefStack.ItemDef);
			
			FHNKItemInstanceStack NewItemStack;
			NewItemStack.ItemInstance = ItemInstance;
			NewItemStack.Count = CountToAdd;
			RemainingCountToAdd -= CountToAdd;
			
			Items.Add(NewItemStack);
			
			LastAddedItemIndex = Items.Num() - 1;
		}
	}
	
	OnRep_Items();
	return LastAddedItemIndex;
}

bool UHNKInventoryComponent::RemoveItem(int32 ItemIndex, int32 Count)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner || !MyOwner->HasAuthority())
	{
		return false;
	}
	
	if (Items.IsValidIndex(ItemIndex))
	{
		if (Count < 0 || Count >= Items[ItemIndex].Count)
		{
			Items.RemoveAt(ItemIndex);
			OnRep_Items();
			return true;
		}
		else
		{
			Items[ItemIndex].Count -= Count;
			return true;
		}
	}
	
	return false;
}

void UHNKInventoryComponent::ServerDropItem_Implementation(int32 ItemIndex)
{
	DropItem(ItemIndex);
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
	
	const UHNKItemFragment_WorldRepresentation* Fragment = Cast<UHNKItemFragment_WorldRepresentation>(Items[ItemIndex].ItemInstance->FindFragmentByClass(UHNKItemFragment_WorldRepresentation::StaticClass()));
	if (!Fragment || !Fragment->bCanBeDropped || !Fragment->ItemDropClass)
	{
		return false;
	}
		
	if (IHNKEquipmentComponentInterface* ECI = Cast<IHNKEquipmentComponentInterface>(GetOwner()))
	{
		if (UHNKEquipmentComponent* EquipmentComponent = ECI->GetEquipmentComponent())
		{
			if (UHNKEquipmentInstance* EquipmentInstance = EquipmentComponent->FindEquipmentByItemInstance(Items[ItemIndex].ItemInstance))
			{
				EquipmentComponent->UnequipItem(EquipmentInstance);
			}
		}
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
	
	FHNKItemDefinitionStack ItemDefStack;
	ItemDefStack.ItemDef = Items[ItemIndex].ItemInstance->ItemDef;
	ItemDefStack.Count = Items[ItemIndex].Count;
	ItemDrop->SetItemStack(ItemDefStack);

	RemoveItem(ItemIndex);
	return true;
}

void UHNKInventoryComponent::ServerUseItem_Implementation(int32 ItemIndex)
{
	UseItem(ItemIndex);
}

bool UHNKInventoryComponent::UseItem(int32 ItemIndex)
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
	
	const UHNKItemFragment_Useable* Fragment = Cast<UHNKItemFragment_Useable>(Items[ItemIndex].ItemInstance->FindFragmentByClass(UHNKItemFragment_Useable::StaticClass()));
	if (!Fragment)
	{
		return false;
	}
	
	const bool bSuccess = Fragment->Use(GetOwner(), Items[ItemIndex].ItemInstance);
	
	if (bSuccess && Fragment->bConsumeOnUse)
	{
		RemoveItem(ItemIndex, 1);
	}
	
	return bSuccess;
}

bool UHNKInventoryComponent::FindItemInstance(TSubclassOf<UHNKItemDefinition> ItemDef, FHNKItemInstanceStack& ItemInstanceStack) const
{
	for (const FHNKItemInstanceStack& Stack : Items)
	{
		if (Stack.ItemInstance && Stack.ItemInstance->ItemDef == ItemDef)
		{
			ItemInstanceStack = Stack;
			return true;
		}
	}
	
	return false;
}

bool UHNKInventoryComponent::FindAllItemInstances(TSubclassOf<UHNKItemDefinition> ItemDef, TArray<FHNKItemInstanceStack>& ItemInstanceStacks) const
{
	bool bSuccess = false;
	
	for (const FHNKItemInstanceStack& Stack : Items)
	{
		if (Stack.ItemInstance && Stack.ItemInstance->ItemDef == ItemDef)
		{
			ItemInstanceStacks.Add(Stack);
			bSuccess = true;
		}
	}
	
	return bSuccess;
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
		const FHNKItemInstanceStack& ItemStack = Items[I];
		
		if (ItemStack.ItemInstance->ItemDef == ItemDef)
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

