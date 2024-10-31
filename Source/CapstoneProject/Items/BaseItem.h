// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CapstoneProject/Interface/InteractInterface.h"
#include "CapstoneProject/Characters/CapstoneProjectCharacter.h"

#include "BaseItem.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	BaseItem = 0,
	ToolItem,
	BuildingItem,
	ConsumableItem
};

UCLASS()
class CAPSTONEPROJECT_API ABaseItem : public AActor , public IInteractInterface
{
	GENERATED_BODY()
	
public:
	///////////////////////////////////////////////////////////////////////////////////////////
	// Interface functions
	virtual void Interact_Implementation(ACapstoneProjectCharacter* Character) override;


public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Variables", meta = (AllowPrivateAccess = true))
	EItemType ItemType;

public:
	FORCEINLINE EItemType GetItemType() { return ItemType; }
	FORCEINLINE void SetItemType(EItemType Type) { ItemType = Type; }
};
