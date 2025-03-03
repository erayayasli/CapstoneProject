// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "InventoryItemSlot.h"
#include "CapstoneProject/Items/ItemBase.h"
#include "InventorySlotContextMenu.generated.h"


UCLASS()
class CAPSTONEPROJECT_API UInventorySlotContextMenu : public UUserWidget
{
	GENERATED_BODY()
public:
    static UInventorySlotContextMenu* ActiveContextMenu;
public:
    virtual void NativeConstruct() override;

    // Set the item this context menu is for
    void SetItemData(UItemBase* Item);

    // Set the parent slot
    void SetParentSlot(UInventoryItemSlot* SlotToSetParent);

    // Actions
    UFUNCTION()
    void OnUseButtonClicked();
    UFUNCTION()
    void OnDropButtonClicked();
  /*  UFUNCTION()
    void OnUseButtonPressed();
    UFUNCTION()
    void OnDropButtonPressed();*/

    UFUNCTION()
    void RemoveMenu();


public:
    UPROPERTY(EditDefaultsOnly, Category = "Variables", meta = (AllowPrivateAccess = true))
    FVector2D SizeOfContextMenu = FVector2D(200.f, 100.f);

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* UseButton;

    UPROPERTY(meta = (BindWidget))
    UButton* DropButton;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* MenuContainer;

    // Parent slot reference
    UPROPERTY()
    UInventoryItemSlot* ParentSlot;

    // Item reference
    UPROPERTY()
    UItemBase* ItemReference;

    // Close this menu if user clicks outside
   // virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


	
};
