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

    // Buton ba�lant�lar�n� temizle ve yeniden ekle
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
    UE_LOG(LogTemp, Warning, TEXT("Use �al���yor"))
    // Handle using the item
    if (ItemReference)
    {
        if (ItemReference->ItemType == EItemType::Weapon)
        {
            ACapstoneProjectCharacter* PlayerCharacter = Cast<ACapstoneProjectCharacter>(GetOwningPlayerPawn());
            if (PlayerCharacter)
            {
                PlayerCharacter->HoldingItemReference = ItemReference;
                PlayerCharacter->HoldingItemMesh->SetStaticMesh(ItemReference->AssetData.Mesh);
            }
            UE_LOG(LogTemp, Warning, TEXT("Weapon  'use' command used."))

        }
        else if (ItemReference->ItemType == EItemType::Consumable)
        {
            UE_LOG(LogTemp, Warning, TEXT("Consumable item 'use' command used."))
        }
    }

    // Close the menu
    RemoveFromParent();
}

void UInventorySlotContextMenu::OnDropButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Drop �al���yor"))

    // Handle dropping the item
    if (ItemReference)
    {
        // Call your item drop function
        ACapstoneProjectCharacter* PlayerCharacter = Cast<ACapstoneProjectCharacter>(GetOwningPlayerPawn());
        if (PlayerCharacter)
        {
            PlayerCharacter->DropItem(ItemReference, ItemReference->Quantity);
            UE_LOG(LogTemp, Warning, TEXT("Esya at�ld�: %d numara"), ItemReference->ItemType);
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