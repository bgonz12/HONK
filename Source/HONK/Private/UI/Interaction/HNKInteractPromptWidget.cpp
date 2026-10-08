// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Interaction/HNKInteractPromptWidget.h"

// HONK Includes
#include "Gameplay/Interaction/HNKInteractionTypes.h"

// Engine Includes
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "UI.InteractPromptWidget"

void UHNKInteractPromptWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	SetInteractProgress(0.f);
}

void UHNKInteractPromptWidget::SetInteractType(EHNKInteractionType InInteractType)
{
	if (Interact_TextBlock)
	{
		FText Action;
		switch (InInteractType)
		{
		case EHNKInteractionType::IT_Press:
			Action = FText::FromString(TEXT("PRESS"));
			break;
			
		case EHNKInteractionType::IT_Hold:
			Action = FText::FromString(TEXT("HOLD"));
			break;
			
		default:
			break;
		}
		
		FText InteractText = FText::Format(NSLOCTEXT(LOCTEXT_NAMESPACE, "Interact_TextBlock", "{0} \"E\" to interact"), Action);
		Interact_TextBlock->SetText(InteractText);
	}
}

void UHNKInteractPromptWidget::SetInteractProgress(float InPercent)
{
	if (Interact_ProgressBar)
	{
		Interact_ProgressBar->SetPercent(InPercent);
	}
}

#undef LOCTEXT_NAMESPACE