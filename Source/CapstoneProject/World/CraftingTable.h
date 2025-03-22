#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CapstoneProject/Interface/InteractInterface.h"
#include "CapstoneProject/Items/ItemBase.h"
#include "CraftingTable.generated.h"

class UItemBase;

UCLASS()
class CAPSTONEPROJECT_API ACraftingTable : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACraftingTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	void InitializePickup();
	void UpdateInteractableData();

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void Interact(ACapstoneProjectCharacter* PlayerCharacter) override;

	UFUNCTION(BlueprintImplementableEvent)
	void InteractBlueprintFunc();
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Pickup | Components")
	UStaticMeshComponent* CraftingTableMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup | Interaction Data", meta = (AllowPrivateAccess = true))
	FInteractableData InstanceInteractableData;

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Item Reference")
	TObjectPtr<UItemBase> ItemReference;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	FDataTableRowHandle ItemRowHandle;
};
