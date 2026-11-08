// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Engine Includes
#include "GameFramework/Actor.h"

// HONK Includes
#include "HNKProjectile.generated.h"

class UGameplayEffect;
class UHNKGagDataAsset;
class UProjectileMovementComponent;
class USphereComponent;

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
	
	USphereComponent* GetCollisionComponent() const;
	
protected:
	void ApplyHitEffects(const FHitResult& HitResult);
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> CollisionComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> HitEffects;
	
	UPROPERTY(EditAnywhere)
	UHNKGagDataAsset* OwnerGagData;
	
	UPROPERTY(EditAnywhere)
	UHNKGagDataAsset* TargetGagData;
};
