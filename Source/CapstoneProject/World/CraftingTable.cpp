#include "CraftingTable.h"

// Sets default values
ACraftingTable::ACraftingTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CraftingTableMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	CraftingTableMesh->SetSimulatePhysics(true);
	SetRootComponent(CraftingTableMesh);
}

// Called when the game starts or when spawned
void ACraftingTable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACraftingTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACraftingTable::InitializePickup()
{
	if (!ItemRowHandle.IsNull())
	{
		const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString());

		ItemReference = NewObject<UItemBase>(this, UItemBase::StaticClass());

		ItemReference->ID = ItemData->ID;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->ItemQuality = ItemData->ItemQuality;
		ItemReference->NumericData = ItemData->NumericData;
		ItemReference->TextData = ItemData->TextData;
		ItemReference->AssetData = ItemData->AssetData;
		ItemReference->ItemStatistics = ItemData->ItemStatistics;

		ItemReference->NumericData.bIsStackable = ItemData->NumericData.MaxStackSize > 1;
		ItemReference->SetQuantity(1);

		CraftingTableMesh->SetStaticMesh(ItemData->AssetData.Mesh);

		UpdateInteractableData();
	}
}

void ACraftingTable::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::CraftingTable;
	InstanceInteractableData.ItemType = ItemReference->ItemType;
	InstanceInteractableData.Action = ItemReference->TextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->TextData.Name;
	InstanceInteractableData.Quantity = ItemReference->Quantity;
	InteractableData = InstanceInteractableData;
}

void ACraftingTable::BeginFocus()
{
	if (CraftingTableMesh)
	{
		CraftingTableMesh->SetRenderCustomDepth(true);
	}
}

void ACraftingTable::EndFocus()
{
	if (CraftingTableMesh)
	{
		CraftingTableMesh->SetRenderCustomDepth(false);
	}
}

void ACraftingTable::Interact(ACapstoneProjectCharacter* PlayerCharacter)
{
	InteractBlueprintFunc();
}





