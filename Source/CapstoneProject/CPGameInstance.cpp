#include "CPGameInstance.h"
#include "CapstoneProject/UserInterface/Inventory/InventorySlotContextMenu.h"

void UCPGameInstance::LoadLevel_Implementation(const FName& LevelToLoad)
{
	LoadLevel(LevelToLoad);
}

void UCPGameInstance::Shutdown()
{
	Super::Shutdown();

	// Static variable to nullptr
	UInventorySlotContextMenu::ActiveContextMenu = nullptr;
}
