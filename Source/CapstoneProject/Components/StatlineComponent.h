// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatlineComponent.generated.h"

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
	GENERATED_USTRUCT_BODY()

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
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UStatlineComponent : public UActorComponent
{
	GENERATED_BODY()


	// Health
	//	Current Value
	//	Max value
	//	Regen rate
	//	float currentHealth
	//  float MaxHealth
	//  float HealthPerSecondTick
	// Stamina
	// Hunger
	// Thirst
	// energy?? sleep???

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FCoreStat Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FCoreStat Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FCoreStat Hunger = FCoreStat(100, 100, -0.125);	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FCoreStat Thirst = FCoreStat(100, 100, -0.25);
	
	void TickStats(const float& DeltaTime);
public:	
	// Sets default values for this component's properties
	UStatlineComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetStatPercentile(const ECoreStat Stat) const;

};
