#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

// HONK Includes
#include "HNKSaveGameSubsystem.generated.h"

class UHNKSaveGame_Player;
class UHNKSaveGame_Session;
class IHNKSaveableObjectInterface;

UENUM(BlueprintType)
enum EHNKSaveType : uint8
{
	ST_None,
	ST_Player,
	ST_Session
};

UCLASS()
class HONK_API UHNKSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	//~Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//~End USubsystem
	
	UFUNCTION(BlueprintCallable)
	virtual bool TrySavingDataToDisk(EHNKSaveType SaveType);

	UFUNCTION(BlueprintCallable)
	virtual bool TryLoadingDataFromDisk(EHNKSaveType SaveType);
	
	virtual void CreateNewSaveGame(EHNKSaveType SaveType);

	UFUNCTION(BlueprintPure)
	UHNKSaveGame* GetSaveGameInstance(EHNKSaveType SaveType) const;
	
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Object"))
	virtual void SaveObject(UObject* Object);
	
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Object"))
	virtual void LoadObject(UObject* Object);
	
public:
	UPROPERTY()
	TObjectPtr<UHNKSaveGame_Player> PlayerSaveGameInstance;
	
	UPROPERTY()
	TObjectPtr<UHNKSaveGame_Session> SessionSaveGameInstance;
};
