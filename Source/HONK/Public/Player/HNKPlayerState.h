#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"

// HONK Includes
#include "Gameplay/HNKDamageableInterface.h"
#include "HNKPlayerState.generated.h"

class UAbilitySystemComponent;
class UDataTable;

UCLASS()
class HONK_API AHNKPlayerState : public APlayerState, public IAbilitySystemInterface, public IHNKDamageableInterface
{
	GENERATED_BODY()
	
public:
	AHNKPlayerState();

	//~Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End IAbilitySystemInterface
	
	void TryTriggerGag(UHNKGagDataAsset* GagData);

protected:
	UFUNCTION(Server, Reliable)
	void Server_TriggerGag(UHNKGagDataAsset* GagData);
	void TriggerGag(UHNKGagDataAsset* GagData);
	
	UFUNCTION(BlueprintNativeEvent)
	void ScoreGag(UHNKGagDataAsset* GagData);
	
protected:
	UPROPERTY()
	bool bAllowGags = true;;
};

inline void AHNKPlayerState::ScoreGag_Implementation(UHNKGagDataAsset* GagData)
{
}
