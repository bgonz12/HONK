// Fill out your copyright notice in the Description page of Project Settings.

// HONK Includes
#include "Gameplay/HNKDamageableInterface.h"

// Add default functionality here for any IHNKDamageableInterface functions that are not pure virtual.

void IHNKDamageableInterface::DamageTaken(FHNKDamagePacket& DamagePacket)
{
}

float IHNKDamageableInterface::GetHealth() const
{
	return -1.f;
}

float IHNKDamageableInterface::GetMaxHealth() const
{
	return -1.f;
}
