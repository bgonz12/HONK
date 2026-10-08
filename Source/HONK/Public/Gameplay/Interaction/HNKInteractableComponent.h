// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "HNKInteractionTypes.h"
#include "Components/SphereComponent.h"

#include "HNKInteractableComponent.generated.h"

enum class EHNKInteractionType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHNKInteractableTriggered, AActor*, InteractingActor, bool, bIsServerInteract);

/**
 * 
 */
UCLASS()
class HONK_API UHNKInteractableComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UHNKInteractableComponent();
	
	//~Begin UActorComponent
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End UActorComponent
	
	void TriggerInteract(AActor* InteractingActor, bool bIsServerInteract);
	
	UFUNCTION(BlueprintPure)
	EHNKInteractionType GetInteractionType() const;
	
	UFUNCTION(BlueprintPure)
	float GetRequiredHoldDuration() const;
	
	UFUNCTION(BlueprintPure)
	void GetInteractionText(FText& OutInteractionText) const;
	
protected:
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	UPROPERTY(BlueprintAssignable)
	FHNKInteractableTriggered OnInteractableTriggered;
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EHNKInteractionType InteractionType = EHNKInteractionType::IT_Press;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition="InteractionType==EHNKInteractionType::IT_Hold", EditConditionHides))
	float RequiredHoldDuration = 1.f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText InteractionText = FText::FromString(FString("Interact"));
};
