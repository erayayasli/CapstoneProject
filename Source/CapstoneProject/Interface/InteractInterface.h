#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CapstoneProject/Items/DataStructs/ItemDataStructs.h"
#include "InteractInterface.generated.h"

class ACapstoneProjectCharacter;

UENUM(BlueprintType)
enum class EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
	Device UMETA(DisplayName = "Device"),
	Toggle UMETA(DisplayName = "Toggle"),//button ,switch, anything that can activate
	Container UMETA(DisplayName = "Container")
};

USTRUCT(BlueprintType)
struct FInteractableData {
	GENERATED_BODY()

	FInteractableData(): 
		InteractableType(EInteractableType::Pickup),
		Name(FText::GetEmpty()),
		Action(FText::GetEmpty()),
		Quantity(0),
		InteractionDuration(0.f)
	{

	};

	UPROPERTY(EditInstanceOnly)
	EInteractableType InteractableType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	UPROPERTY(EditInstanceOnly)
	int32 Quantity; // Just for pickups

	UPROPERTY(EditInstanceOnly)
	float InteractionDuration; // Use for things valves , doors etc. that requires an interaction time
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAPSTONEPROJECT_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(class ACapstoneProjectCharacter* PlayerCharacter);

	FInteractableData InteractableData;
};
