// Fill out your copyright notice in the Description page of Project Settings.


#include "StatlineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DamageComponent.h"

void UStatlineComponent::TickStats(const float& DeltaTime)
{
	TickStamina(DeltaTime);
	TickHunger(DeltaTime);
	TickThirst(DeltaTime);
	if (Thirst.GetCurrent() <= 0.0 || Hunger.GetCurrent() <= 0.0)
	{
		return;
	}
}

void UStatlineComponent::TickStamina(const float& DeltaTime)
{
	if (CurrentStaminaExhaustion > 0.0)
	{
		CurrentStaminaExhaustion -= DeltaTime;
		return;
	}

	if (bIsSprinting && IsValidSpriting())
	{
		Stamina.TickStat(0 - (DeltaTime * SprintCostMultiplier));
		if (Stamina.GetCurrent() <= 0)
		{
			SetSprinting(false);
			CurrentStaminaExhaustion = SecondsForStaminaExhaustion;
		}
		return;
	}

	if (!bIsSprinting && !OwningCharacterMovementComp->IsFalling()) // Stamina Regen
	{
		Stamina.TickStat(0 + (DeltaTime * SprintRegenerationPerSecond));
	}
}

void UStatlineComponent::TickHunger(const float& DeltaTime)
{
	if (Hunger.GetCurrent() <= 0.0)
	{
		//Little bit confusing but it sets health between current and maxhealth 
		OwningDamageComponent->Health = FMath::Clamp(OwningDamageComponent->Health + 0 - abs(StarvingHealthDamagePerSecond * DeltaTime), 0, OwningDamageComponent->MaxHealth);
		return;
	}

	Hunger.TickStat(DeltaTime);
}

void UStatlineComponent::TickThirst(const float& DeltaTime)
{
	if (Thirst.GetCurrent() <= 0.0)
	{
		//Same as tick hunger
		OwningDamageComponent->Health = FMath::Clamp(OwningDamageComponent->Health + 0 - abs(DehydrationHealthDamagePerSecond * DeltaTime), 0, OwningDamageComponent->MaxHealth);
		return;
	}

	Thirst.TickStat(DeltaTime);
}

bool UStatlineComponent::IsValidSpriting()
{
	return OwningCharacterMovementComp->Velocity.Length() > WalkSpeed && !OwningCharacterMovementComp->IsFalling();
}

// Called when the game starts
void UStatlineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Sets default values for this component's properties
UStatlineComponent::UStatlineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
// Called every frame
void UStatlineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TickType != LEVELTICK_PauseTick)
	{
		TickStats(DeltaTime);
	}
}

void UStatlineComponent::SetMovementCompReference(UCharacterMovementComponent* Comp)
{
	OwningCharacterMovementComp = Comp;
}

void UStatlineComponent::SetDamageCompReference(UDamageComponent* Comp)
{
	OwningDamageComponent = Comp;
}

float UStatlineComponent::GetStatPercentile(const ECoreStat Stat) const
{
	switch (Stat)
	{
	case ECoreStat::CS_Stamina:
		return Stamina.Percentile();

	case ECoreStat::CS_Hunger:
		return Hunger.Percentile();

	case ECoreStat::CS_Thirst:
		return Thirst.Percentile();

	default:
		return -1;//Invalid LOG. TODO
	}
}

bool UStatlineComponent::CanSprint() const
{
	return Stamina.GetCurrent() > 0.0f;
}

void UStatlineComponent::SetSprinting(const bool& IsSprinting)
{
	bIsSprinting = IsSprinting;
	if (bIsSneaking && !bIsSprinting)
	{
		return;
	}
	bIsSneaking = false;
	OwningCharacterMovementComp->MaxWalkSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
}

void UStatlineComponent::SetSneaking(const bool& IsSneaking)
{
	bIsSneaking = IsSneaking;
	if (bIsSprinting && !bIsSneaking)
	{
		return;
	}
	bIsSprinting = false;
	OwningCharacterMovementComp->MaxWalkSpeed = bIsSneaking ? SneakSpeed : WalkSpeed;
}

bool UStatlineComponent::CanJump()
{
	return Stamina.GetCurrent() >= JumpCost;
}

void UStatlineComponent::HasJumped()
{
	Stamina.Adjust(JumpCost * -1);
}