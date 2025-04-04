// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CapstoneProject/DataType/StructsClassesEnums.h"
#include "StatlineComponent.generated.h"


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

public:
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Stats", meta = (AllowPrivateAccess = "true"))
	FCoreStat Health;	*/						 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Stats", meta = (AllowPrivateAccess = "true"))
	FCoreStat Stamina;							 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Stats", meta = (AllowPrivateAccess = "true"))
	FCoreStat Hunger = FCoreStat(100, 100, -0.35);	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Stats", meta = (AllowPrivateAccess = "true"))
	FCoreStat Thirst = FCoreStat(100, 100, -0.55);
	
	void TickStats(const float& DeltaTime);
	void TickStamina(const float& DeltaTime);
	void TickHunger(const float& DeltaTime);
	void TickThirst(const float& DeltaTime);

	//Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsSprinting = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsSneaking = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SprintCostMultiplier = 2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SprintRegenerationPerSecond = 7;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float JumpCost = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 300;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 550;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SneakSpeed = 150;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SecondsForStaminaExhaustion = 5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float CurrentStaminaExhaustion = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float StarvingHealthDamagePerSecond = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float DehydrationHealthDamagePerSecond = 1;

	bool IsValidSpriting();
	class UCharacterMovementComponent* OwningCharacterMovementComp;
	class UDamageComponent* OwningDamageComponent;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets default values for this component's properties
	UStatlineComponent();

	UFUNCTION(BlueprintCallable)
	void SetMovementCompReference(UCharacterMovementComponent* Comp);

	UFUNCTION(BlueprintCallable)
	void SetDamageCompReference(UDamageComponent* Comp);

	UFUNCTION(BlueprintCallable)
	float GetStatPercentile(const ECoreStat Stat) const;

	UFUNCTION(BlueprintCallable)
	bool CanSprint() const;
	UFUNCTION(BlueprintCallable)
	void SetSprinting(const bool& IsSprinting);
	UFUNCTION(BlueprintCallable)
	void SetSneaking(const bool& IsSneaking);
	UFUNCTION(BlueprintCallable)
	bool CanJump();
	UFUNCTION(BlueprintCallable)
	void HasJumped();


};
