// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Item/HNKItemEquip.h"

// HONK Includes
#include "Inventory/Item/HNKItemAttachment.h"

AHNKItemEquip::AHNKItemEquip()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHNKItemEquip::Destroyed()
{
	if (IsValid(ItemAttachmentActor))
	{
		ItemAttachmentActor->Destroy();
	}
	
	Super::Destroyed();
}

void AHNKItemEquip::SetItemAttachmentActor(AHNKItemAttachment* InItemAttachmentActor)
{
	ItemAttachmentActor = InItemAttachmentActor;
}

void AHNKItemEquip::SetItemDropActor(AHNKItemDrop* InItemDropActor)
{
	ItemDropActor = InItemDropActor;
}

