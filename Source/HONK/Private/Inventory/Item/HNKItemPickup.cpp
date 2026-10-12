// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/HNKItemPickup.h"

#include "Gameplay/Interaction/HNKInteractableComponent.h"
#include "Inventory/Item/HNKItemDefinition.h"
#include "Inventory/Item/HNKItemInstance.h"

#define LOCTEXT_NAMESPACE "ItemPickup"

AHNKItemPickup::AHNKItemPickup()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);
	
	InteractableComponent = CreateDefaultSubobject<UHNKInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(RootComponent);
}

void AHNKItemPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	static const FName Name_ItemStack = GET_MEMBER_NAME_CHECKED(AHNKItemPickup, ItemStack);

	FProperty* MemberPropertyThatChanged = PropertyChangedEvent.MemberProperty;
	const FName MemberPropertyName = MemberPropertyThatChanged != NULL ? MemberPropertyThatChanged->GetFName() : NAME_None;

	if (MemberPropertyName == Name_ItemStack)
	{
		if (ItemStack.ItemDef)
		{
			if (UHNKItemDefinition* ItemDefCDO = ItemStack.ItemDef->GetDefaultObject<UHNKItemDefinition>())
			{
				FText ItemNameText = ItemDefCDO->ItemName;
				FText ItemCountText = ItemStack.Count > 1 ? FText::Format(NSLOCTEXT(LOCTEXT_NAMESPACE, "InteractionText", " x{0}"), ItemStack.Count) : FText();
		
				FText InteractionText = FText::Format(NSLOCTEXT(LOCTEXT_NAMESPACE, "InteractionText", "To Pickup {0}{1}"), ItemNameText, ItemCountText);
				InteractableComponent->SetInteractionText(InteractionText);
			}
		
		}
	}
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#undef LOCTEXT_NAMESPACE
