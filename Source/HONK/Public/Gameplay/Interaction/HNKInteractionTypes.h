// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EHNKInteractionType : uint8
{
	IT_Press UMETA(DisplayName="Press"),
	IT_Hold UMETA(DisplayName="Hold")
};