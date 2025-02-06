// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryPanel.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void RefreshInventory();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWrapBox> InventoryWrapBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> WeightInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CapacityInfo;

	UPROPERTY()
	TObjectPtr<class ACapstoneProjectCharacter> PlayerCharacter;
	UPROPERTY()
	TObjectPtr<class UInventoryComponent> InventoryReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UInventoryItemSlot> InventorySlotClass;

protected:

	void SetInfoText() const;
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
