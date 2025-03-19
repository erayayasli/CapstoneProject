#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Consumable UMETA(DisplayName = "Consumable"),
	Resource UMETA(DisplayName = "Resource"),
	Tool UMETA(DisplayName = "Tool")
};

USTRUCT(BlueprintType)
struct FEffectOnStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float HealthEffect;

	UPROPERTY(EditAnywhere)
	float HungerEffect;

	UPROPERTY(EditAnywhere)
	float ThirstEffect;

	UPROPERTY(EditAnywhere)
	float StaminaEffect;
};

USTRUCT(BlueprintType)
struct FItemStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float DamageValue;

	UPROPERTY(EditAnywhere)
	float RestorationAmount;

	UPROPERTY(EditAnywhere)
	float SellValue;
	
	UPROPERTY(EditAnywhere)
	FEffectOnStats StatValues;
};

USTRUCT(BlueprintType)
struct FItemTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	FText InteractionText;

	UPROPERTY(EditAnywhere)
	FText UsageText;
};

USTRUCT(BlueprintType)
struct FItemNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Weight;

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;

	UPROPERTY()
	bool bIsStackable;
};

USTRUCT(BlueprintType)
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere)
	USoundCue* CueToUse;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData NumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;
};