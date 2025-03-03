// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UCPGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName CurrentlyLoadedLevel = "NONE";


	UFUNCTION(BlueprintCallable)
	bool NoLevelLoaded() const { return CurrentlyLoadedLevel == "NONE"; }

public:
	UFUNCTION(BlueprintNativeEvent)
	void LoadLevel(const FName& LevelToLoad);
	UFUNCTION(BlueprintCallable)
	void LoadLevel_Implementation(const FName& LevelToLoad);
};
