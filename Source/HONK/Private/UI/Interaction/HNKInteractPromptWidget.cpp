// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Interaction/HNKInteractPromptWidget.h"

// HONK Includes
#include "Gameplay/Interaction/HNKInteractionTypes.h"

// Engine Includes
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Gameplay/Interaction/HNKInteractableComponent.h"

#define LOCTEXT_NAMESPACE "UI.InteractPromptWidget"

void UHNKInteractPromptWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	SetInteractProgress(0.f);
}

void UHNKInteractPromptWidget::UpdateInteractText(UHNKInteractableComponent* InteractableComponent)
{
	if (Interact_TextBlock)
	{
		FText InteractionTypeText;
		switch (InteractableComponent->GetInteractionType())
		{
		case EHNKInteractionType::IT_Press:
			InteractionTypeText = FText::FromString(TEXT("PRESS"));
			break;
			
		case EHNKInteractionType::IT_Hold:
			InteractionTypeText = FText::FromString(TEXT("HOLD"));
			break;
			
		default:
			break;
		}
		
		FText InteractionText;
		InteractableComponent->GetInteractionText(InteractionText);
		
		FText InteractText = FText::Format(NSLOCTEXT(LOCTEXT_NAMESPACE, "Interact_TextBlock", "{0} \"E\" {1}"), InteractionTypeText, InteractionText);
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