// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructsClassesEnums.generated.h"

UENUM(BlueprintType)
enum class ECoreStat : uint8
{
	CS_Health UMETA(DisplayName = "Health"),
	CS_Stamina UMETA(DisplayName = "Stamina"),
	CS_Hunger UMETA(DisplayName = "Hunger"),
	CS_Thirst UMETA(DisplayName = "Thirst")
};


USTRUCT(BlueprintType)
struct FCoreStat
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Current = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Max = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float PerSecondTick = 1;

public:
	FCoreStat()
	{

	};
	FCoreStat(const float& current, const float& max, const float& tick)
	{
		Current = current;
		Max = max;
		PerSecondTick = tick;
	};

	//UFUNCTION(BlueprintCallable)
	void TickStat(const float& DeltaTime)
	{
		Current = FMath::Clamp(Current + (PerSecondTick * DeltaTime), 0, Max);
	}


	void Adjust(const float& Amount)
	{
		Current = FMath::Clamp(Current + Amount, 0, Max);
	}

	float Percentile() const
	{
		return Current / Max;
	}

	void AdjustTick(const float& NewTick)
	{
		PerSecondTick = NewTick;
	}
	float GetCurrent() const
	{
		return Current;
	}
};

UENUM(BlueprintType)
enum class EDamageResponse : uint8
{
	None        UMETA(DisplayName = "None"),
	HitReaction     UMETA(DisplayName = "HitReaction"),
	Stagger     UMETA(DisplayName = "Stagger"),
	Stun       UMETA(DisplayName = "Stun"),
	KnockBack       UMETA(DisplayName = "KnockBack")
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	None        UMETA(DisplayName = "None"),
	Melee     UMETA(DisplayName = "Melee"),
	Projectile     UMETA(DisplayName = "Projectile"),
	Explosion       UMETA(DisplayName = "Explosion"),
	Environment       UMETA(DisplayName = "Environment")
};

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EDamageResponse DamageResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool ShouldDamageInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool CanBeBlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool CanBeParried;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool ShouldForceInterrupt;
};