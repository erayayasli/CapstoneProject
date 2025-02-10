// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTooltip.h"
#include "InventoryItemSlot.h"

#include "CapstoneProject/Items/ItemBase.h"

#include "Components/TextBlock.h"

void UInventoryTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	if (const UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference())
	{
		switch (ItemBeingHovered->ItemQuality)
		{
			case EItemQuality::Uncommon:
			ItemType->SetColorAndOpacity(FLinearColor::Gray);
			break;
		case EItemQuality::Common:
			ItemType->SetColorAndOpacity(FLinearColor(0.196f, 0.804f, 0.196f));
			break;
		case EItemQuality::Rare:
			ItemType->SetColorAndOpacity(FLinearColor(0.0f, 1.0f, 1.0f));
			break;
		case EItemQuality::Epic:
			ItemType->SetColorAndOpacity(FLinearColor(0.933f, 0.510f, 0.933f));
			break;
		case EItemQuality::Legendary:
			ItemType->SetColorAndOpacity(FLinearColor(1.0f, 0.843f, 0.0f));
			break;
		default:;
		}

		switch (ItemBeingHovered->ItemType)
		{
		case EItemType::Armor:
			ItemType->SetText(FText::FromString("Armor"));
			break;

		case EItemType::Weapon:
			ItemType->SetText(FText::FromString("Weapon"));
			ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
			break;

		case EItemType::Shield:
			ItemType->SetText(FText::FromString("Shield"));
			break;

		case EItemType::Spell:
			ItemType->SetText(FText::FromString("Spell"));
			ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
			break;

		case EItemType::Consumable:
			ItemType->SetText(FText::FromString("Consumable"));
			DamageValue->SetVisibility(ESlateVisibility::Collapsed);
			ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
			break;

		case EItemType::Quest:
			ItemType->SetText(FText::FromString("Quest"));
			ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
			break;

		case EItemType::Mundane:
			ItemType->SetText(FText::FromString("Mundane"));
			DamageValue->SetVisibility(ESlateVisibility::Collapsed);
			ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
			UsageText->SetVisibility(ESlateVisibility::Collapsed);
			break;

		default:;
		}

		ItemName->SetText(ItemBeingHovered->TextData.Name);
		DamageValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.DamageValue));
		ArmorRating->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.ArmorRating));
		UsageText->SetText(ItemBeingHovered->TextData.UsageText);
		ItemDescription->SetText(ItemBeingHovered->TextData.Description);

		const FString WeightInfo =
		{ "Weight: " + FString::SanitizeFloat(ItemBeingHovered->GetItemStackWeight()) };

		StackWeight->SetText(FText::FromString(WeightInfo));

		if (ItemBeingHovered->NumericData.bIsStackable)
		{
			const FString StackInfo =
			{ "Max stack size: " + FString::FromInt(ItemBeingHovered->NumericData.MaxStackSize) };

			MaxStackSize->SetText(FText::FromString(StackInfo));
		}
		else
		{
			MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}