// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "GameFramework/Actor.h"

// HONK Includes
#include "HNKProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class HONK_API AHNKProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AHNKProjectile();

	//~Begin AActor
	virtual void BeginPlay() override;
	//~End AActor
	
	UFUNCTION()
	void ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	
	void ProjectileImpact(const FHitResult& Hit);
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> CollisionComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
};
