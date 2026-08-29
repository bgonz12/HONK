// Fill out your copyright notice in the Description page of Project Settings.

// HONK Includes
#include "Gameplay/HNKDamageableInterface.h"

void IHNKDamageableInterface::ModifyDamage(FHNKDamagePacket& DamagePacket)
{
}

void IHNKDamageableInterface::DamageTaken(const FHNKDamagePacket& DamagePacket)
{
}

void IHNKDamageableInterface::DamageDealt(const FHNKDamagePacket& DamagePacket)
{
}

void IHNKDamageableInterface::Died(const FHNKDamagePacket& DamagePacket)
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
