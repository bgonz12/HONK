// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "GameFramework/Actor.h"

// HONK Includes
#include "HNKItemEquip.generated.h"

class AHNKEquipmentAttachment;

UCLASS()
class HONK_API AHNKItemEquip : public AActor
{
	GENERATED_BODY()
	
public:	
	AHNKItemEquip();

	//~Begin AActor
	virtual void Destroyed() override;
	//~End AActor
	
protected:
	UFUNCTION(BlueprintCallable)
	void SetItemAttachmentActor(AHNKEquipmentAttachment* InItemAttachmentActor);
	
	UFUNCTION(BlueprintCallable)
	void SetItemDropActor(AHNKItemDrop* InItemDropActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHNKEquipmentAttachment> ItemAttachmentClass;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TObjectPtr<AHNKEquipmentAttachment> ItemAttachmentActor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHNKItemDrop> ItemDropClass;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TObjectPtr<AHNKItemDrop> ItemDropActor;
};
