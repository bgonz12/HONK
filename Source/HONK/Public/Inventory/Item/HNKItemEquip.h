// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "GameFramework/Actor.h"

// HONK Includes
#include "HNKItemEquip.generated.h"

class AHNKItemAttachment;

UCLASS()
class HONK_API AHNKItemEquip : public AActor
{
	GENERATED_BODY()
	
public:	
	AHNKItemEquip();

	//~ Begin AActor
	virtual void Destroyed() override;
	//~ End AActor
	
protected:
	UFUNCTION(BlueprintCallable)
	void SetItemAttachmentActor(AHNKItemAttachment* InItemAttachmentActor);
	
	UFUNCTION(BlueprintCallable)
	void SetItemDropActor(AHNKItemDrop* InItemDropActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHNKItemAttachment> ItemAttachmentClass;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TObjectPtr<AHNKItemAttachment> ItemAttachmentActor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHNKItemDrop> ItemDropClass;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TObjectPtr<AHNKItemDrop> ItemDropActor;
};
