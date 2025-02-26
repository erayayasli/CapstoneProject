// Fill out your copyright notice in the Description page of Project Settings.


#include "StatlineComponent.h"

void UStatlineComponent::TickStats(const float& DeltaTime)
{
	Health.TickStat(DeltaTime);
	Stamina.TickStat(DeltaTime);
	Hunger.TickStat(DeltaTime);
	Thirst.TickStat(DeltaTime);
}


// Sets default values for this component's properties
UStatlineComponent::UStatlineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatlineComponent::BeginPlay()
{
	Super::BeginPlay();

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

float UStatlineComponent::GetStatPercentile(const ECoreStat Stat) const
{
	switch (Stat)
	{
	case ECoreStat::CS_Health:
		return Health.Percentile();

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
