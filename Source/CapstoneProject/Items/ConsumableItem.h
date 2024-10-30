// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapstoneProject/Items/BaseItem.h"
#include "CapstoneProject/Characters/CapstoneProjectCharacter.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API AConsumableItem : public ABaseItem
{
	GENERATED_BODY()
public:
	virtual void Interact_Implementation(ACapstoneProjectCharacter* Character) override;

};
