
#include "MainMenu.h"
#include "CapstoneProject/Characters/CapstoneProjectCharacter.h"
void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<ACapstoneProjectCharacter>(GetOwningPlayerPawn());
}

bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//Cast operation to drag drop, ensure player is valid, call drop item on player

	//const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	//if (PlayerCharacter && ItemDragDrop->SourceItem)
	//{
	//	PlayerCharacter->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
	//	return true;
	//}
	return false;
}
