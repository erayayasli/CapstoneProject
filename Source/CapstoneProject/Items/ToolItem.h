// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapstoneProject/Items/BaseItem.h"
#include "CapstoneProject/Characters/CapstoneProjectCharacter.h"
#include "ToolItem.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API AToolItem : public ABaseItem
{
	GENERATED_BODY()
public:
	AToolItem();

public:
	virtual void Interact_Implementation(ACapstoneProjectCharacter* Character) override;
};
