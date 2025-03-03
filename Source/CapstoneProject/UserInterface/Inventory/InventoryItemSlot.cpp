// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemSlot.h"
#include "InventoryPanel.h"
#include "InventoryPanel.h"
#include "ItemDragDropOperation.h"
#include "InventoryTooltip.h"
#include "DragItemVisual.h"
#include "InventorySlotContextMenu.h"

#include "CapstoneProject/Characters/CapstoneProjectCharacter.h"
#include "CapstoneProject/Components/InventoryComponent.h"
#include "CapstoneProject/Items/ItemBase.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"


void UInventoryItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (ToolTipClass)
	{
		UInventoryTooltip* ToolTip = CreateWidget<UInventoryTooltip>(this, ToolTipClass);
		ToolTip->InventorySlotBeingHovered = this;
		SetToolTip(ToolTip);
	}
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemReference)
	{
		switch (ItemReference->ItemQuality)
		{
		case EItemQuality::Uncommon:
			ItemBorder->SetBrushColor(FLinearColor::Gray);
			break;
		case EItemQuality::Common:
			ItemBorder->SetBrushColor(FLinearColor(0.196f, 0.804f, 0.196f));
			break;
		case EItemQuality::Rare:
			ItemBorder->SetBrushColor(FLinearColor(0.0f, 1.0f, 1.0f));
			break;
		case EItemQuality::Epic:
			ItemBorder->SetBrushColor(FLinearColor(0.933f, 0.510f, 0.933f));
			break;
		case EItemQuality::Legendary:
			ItemBorder->SetBrushColor(FLinearColor(1.0f, 0.843f, 0.0f));
			break;
		default:;
		}

		ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);

		if (ItemReference->NumericData.bIsStackable)
		{
			ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	// submenu on right click will happen here //TODO: SA? TIKLAYINCA HER E?YAYA GÖRE B?R MENÜ ÇIKACAK: KULLAN EL?NE AL CART CURT.
	else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		// Right-click detected, show context menu
		CreateContextMenu(InGeometry, InMouseEvent);

		return Reply.Handled();
	}
	return Reply.Unhandled();
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (DragItemVisualClass)
	{
		const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);
		DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);
		DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());

		ItemReference->NumericData.bIsStackable
			? DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity))
			: DragVisual->ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);

		UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
		DragItemOperation->SourceItem = ItemReference;
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;

		DragItemOperation->DefaultDragVisual = DragVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft;

		OutOperation = DragItemOperation;
	}
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryItemSlot::CreateContextMenu(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// First, remove any existing context menu
	RemoveExistingContextMenu();

	// Create context menu widget
	UInventorySlotContextMenu* ContextMenu = CreateWidget<UInventorySlotContextMenu>(GetOwningPlayer(), InventorySlotContextMenuClass);
	if (!ContextMenu)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create context menu widget!"));
		return;
	}

	// Set the associated item for the context menu
	ContextMenu->SetItemData(ItemReference);
	ContextMenu->SetParentSlot(this);

	// Add to viewport to ensure it appears on top
	if (APlayerController* PC = GetOwningPlayer())
	{
		// Mouse pozisyonunu al
		FVector2D MousePosition;
		if (UWidgetLayoutLibrary::GetMousePositionScaledByDPI(UGameplayStatics::GetPlayerController(PC->GetWorld(), 0), MousePosition.X, MousePosition.Y))
		{
			// Konumu ayarla
			ContextMenu->SetRenderTranslation(MousePosition);
			ContextMenu->AddToViewport(9999); // High Z-order to be on top
			
			ContextMenu->SetDesiredSizeInViewport(ContextMenu->SizeOfContextMenu);
		}
	}
}
void UInventoryItemSlot::RemoveExistingContextMenu()
{
	// Find and remove any existing context menus
	TArray<UUserWidget*> AllWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), AllWidgets, UInventorySlotContextMenu::StaticClass(), false);

	for (UUserWidget* Widget : AllWidgets)
	{
		UInventorySlotContextMenu* ContextMenu = Cast<UInventorySlotContextMenu>(Widget);
		if (ContextMenu)
		{
			ContextMenu->RemoveFromParent();
		}
	}
}