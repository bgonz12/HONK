// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "Components/ActorComponent.h"

// HONK Includes
#include "HNKInventoryComponent.generated.h"

class UHNKItemDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHNKOnInventoryChanged, UHNKInventoryComponent*, InventoryComponent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HONK_API UHNKInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHNKInventoryComponent();
	
	//~Begin UObject
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~End UObject
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool AddItem(UPARAM(ref) FHNKItemStack& InOutNewItem);
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool RemoveItem(int32 ItemIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool DropItem(int32 ItemIndex);

protected:
	UFUNCTION()
	void OnRep_Items();
	
	int32 FindStackWithEmptySpace(TSubclassOf<UHNKItemDefinition> ItemDef) const;

	bool GetDropTransform(FTransform& OutTransform) const;
	
protected:
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FHNKOnInventoryChanged OnInventoryChanged;
	
	UPROPERTY(ReplicatedUsing=OnRep_Items, VisibleInstanceOnly, BlueprintReadWrite)
	TArray<FHNKItemStack> Items;
};
