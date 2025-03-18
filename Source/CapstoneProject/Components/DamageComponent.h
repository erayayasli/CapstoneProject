// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    // Health Values
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth;

    // Situation Booleans
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bIsInvincible;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bIsDead;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bIsInterruptible;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bIsBlocking;

    // Attack Tokens
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    int32 AttackTokensCount;

    // Damage Taking Functions
    UFUNCTION(BlueprintCallable, Category = "Damage")
    float Heal(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Damage")
    bool TakeDamage(const FDamageInfo& DamageInfo, AActor* DamageCauser);

    UFUNCTION(BlueprintCallable, Category = "Attack")
    void ReserveAttackToken(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Attack")
    void ReturnAttackToken(int32 Amount);


    //******************************************************Dispatcherları ayarla**************************************************//
    //Event Dispatcher Delegate Definitions
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBlockedSignature, bool, CanBeParried, AActor*, DamageCauser);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageResponseSignature, EDamageResponse, DamageResponse);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

    // Event Dispatchers
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnBlockedSignature OnBlocked;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDamageResponseSignature OnDamageResponse;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDeathSignature OnDeath;

    // Damageability Macro (BlueprintPure)
    UFUNCTION(BlueprintPure, Category = "Damage")
    void CanBeDamaged(bool ShouldDamageInvincible, bool CanBeBlocked, bool& BlockDamage, bool& DoDamage, bool& NoDamage);

};
