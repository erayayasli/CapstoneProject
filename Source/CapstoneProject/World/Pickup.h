
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CapstoneProject/Interface/InteractInterface.h"
#include "Pickup.generated.h"

class UItemBase;
class ACapstoneProjectCharacter;

UCLASS()
class CAPSTONEPROJECT_API APickup : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:

	APickup();
	void InitializePickup(const int32 InQuantity);

	UFUNCTION(BlueprintCallable)
	void InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UItemBase* GetItemData() const { return ItemReference; };

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void Interact(ACapstoneProjectCharacter* PlayerCharacter) override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Item Reference")
	TObjectPtr<UItemBase> ItemReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup | Interaction Data", meta = (AllowPrivateAccess = true))
	FInteractableData InstanceInteractableData;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	int32 ItemQuantity;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	FDataTableRowHandle ItemRowHandle;

protected:
	virtual void BeginPlay() override;

	void UpdateInteractableData();

	void TakePickup(const ACapstoneProjectCharacter* Taker);


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

};
