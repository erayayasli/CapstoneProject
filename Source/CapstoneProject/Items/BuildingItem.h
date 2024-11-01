// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapstoneProject/Items/BaseItem.h"
#include "CapstoneProject/Characters/CapstoneProjectCharacter.h"
#include "BuildingItem.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API ABuildingItem : public ABaseItem
{
	GENERATED_BODY()
public:
	ABuildingItem();

public:
	//virtual void Interact_Implementation(ACapstoneProjectCharacter* Character) override;
	
};
