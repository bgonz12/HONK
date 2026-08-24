#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

// HONK Includes
#include "HNKSaveGameSubsystem.generated.h"

class UHNKSaveGame_Session;
class IHNKSaveableObjectInterface;

UCLASS()
class HONK_API UHNKSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	//~Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//~End USubsystem
	
	UFUNCTION(BlueprintCallable)
	virtual bool TryLoadSession();
	
	UFUNCTION(BlueprintCallable)
	virtual bool SaveSession();

	virtual void CreateNewSessionSaveGame();

	UFUNCTION(BlueprintPure)
	UHNKSaveGame_Session* GetSessionSaveGameInstance() const;
	
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Object"))
	virtual void SaveObject(UObject* Object);
	
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Object"))
	virtual void LoadObject(UObject* Object);
	
public:
	UPROPERTY()
	TObjectPtr<UHNKSaveGame_Session> SessionSaveGameInstance;
};
