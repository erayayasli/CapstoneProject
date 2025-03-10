#include "InventorySlotContextMenu.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "CapstoneProject/Characters/CapstoneProjectCharacter.h"

UInventorySlotContextMenu* UInventorySlotContextMenu::ActiveContextMenu = nullptr;

void UInventorySlotContextMenu::NativeConstruct()
{
    Super::NativeConstruct();

    // Set this as the active context menu
    ActiveContextMenu = this;

    // Buton baðlantýlarýný temizle ve yeniden ekle
    if (UseButton)
    {
        UseButton->OnClicked.Clear();
        UseButton->OnClicked.AddDynamic(this, &UInventorySlotContextMenu::OnUseButtonClicked);
    }

    if (DropButton)
    {
        DropButton->OnClicked.Clear();
        DropButton->OnClicked.AddDynamic(this, &UInventorySlotContextMenu::OnDropButtonClicked);
    }

}

void UInventorySlotContextMenu::SetItemData(UItemBase* Item)
{
    ItemReference = Item;

    // Update UI based on item if needed
    // e.g., disable Use button if item can't be used
}

void UInventorySlotContextMenu::SetParentSlot(UInventoryItemSlot* SlotToSetParent)
{
    ParentSlot = SlotToSetParent;
}

void UInventorySlotContextMenu::OnUseButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Use çalýþýyor"))
    // Handle using the item
    ACapstoneProjectCharacter* PlayerCharacter = Cast<ACapstoneProjectCharacter>(GetOwningPlayerPawn());
    if (ItemReference && PlayerCharacter)
    {
        PlayerCharacter->HoldingItemReference = ItemReference;

        if (ItemReference->ItemType == EItemType::Weapon)
        {
            PlayerCharacter->HoldingItemMesh->SetRelativeLocation(FVector(70.f, 40.f, -40.f)); //TODO: make it variable inside character.ccp
            PlayerCharacter->HoldingItemMesh->SetRelativeRotation(FRotator(90, 60.f, 0.f));
            PlayerCharacter->HoldingItemMesh->SetStaticMesh(ItemReference->AssetData.Mesh);
            UE_LOG(LogTemp, Warning, TEXT("Weapon  'use' command used."))
        }
        else if (ItemReference->ItemType == EItemType::Consumable)
        {
            //TODO: BURAYA  DATA TABLE DAKI YIYECEKLERIN NE KADAR CAN ARTTIRACAÐI NE KADAR SURE ARTTIRACAÐI FALAN O BILGILERI ÇEKIP
            //      INVENTORY COMPONENTTAN GUNCELLEME YAP
            UE_LOG(LogTemp, Warning, TEXT("Consumable item 'use' command used."))
        }
    }

    // Close the menu
    RemoveFromParent();
}

void UInventorySlotContextMenu::OnDropButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Drop çalýþýyor"))

    // Handle dropping the item
    if (ItemReference)
    {
        // Call your item drop function
        ACapstoneProjectCharacter* PlayerCharacter = Cast<ACapstoneProjectCharacter>(GetOwningPlayerPawn());
        if (PlayerCharacter)
        {
            PlayerCharacter->DropItem(ItemReference, ItemReference->Quantity);
            UE_LOG(LogTemp, Warning, TEXT("Esya atýldý: %d numara"), ItemReference->ItemType);
        }

    }

    // Close the menu
    RemoveFromParent();
}


void UInventorySlotContextMenu::RemoveMenu()
{
    if (ActiveContextMenu == this)
    {
        ActiveContextMenu = nullptr;
    }
    RemoveFromParent();
}