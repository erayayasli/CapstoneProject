
#include "DamageComponent.h"
#include "CapstoneProject/DataType/StructsClassesEnums.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = 100.f;
	MaxHealth = 100.f;
	bIsInvincible = false;
	bIsDead = false;
	bIsInterruptible = true;
	bIsBlocking = false;
	AttackTokensCount = 0;
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


float UDamageComponent::Heal(float Amount)
{
	if (!bIsDead)
	{
		Health = FMath::Clamp(Health + Amount, 0.f, MaxHealth);
		return Health;
	}
	return -1;
}

bool UDamageComponent::TakeDamage(const FDamageInfo& DamageInfo, AActor* DamageCauser)
{
    bool BlockDamage, DoDamage, NoDamage;

    // Get the output values ​​by calling the CanBeDamaged function
    CanBeDamaged(DamageInfo.ShouldDamageInvincible, DamageInfo.CanBeBlocked, BlockDamage, DoDamage, NoDamage);

    // If damage is blocked, trigger the OnBlocked event
    if (BlockDamage)
    {
        OnBlocked.Broadcast(DamageInfo.CanBeParried, DamageCauser);
        return false; // Hasar alınmadı
    }

    // If the damage is completely prevented (NoDamage), do nothing
    if (NoDamage)
    {
        return false; // Hasar alınmadı
    }

    // If damage can be taken (DoDamage), reduce health value
    if (DoDamage)
    {
        Health -= DamageInfo.Amount;

        // Eğer sağlık sıfıra düştüyse, ölü duruma geç
        if (Health <= 0.f)
        {
            bIsDead = true;
            OnDeath.Broadcast();
        }

        // Trigger damage reaction event
        OnDamageResponse.Broadcast(DamageInfo.DamageResponse);

        return true; // Damage Taken
    }

    return false; // No damage taken by default
}

void UDamageComponent::ReserveAttackToken(int32 Amount)
{
}

void UDamageComponent::ReturnAttackToken(int32 Amount)
{
}

void UDamageComponent::CanBeDamaged(bool ShouldDamageInvincible, bool CanBeBlocked, bool& BlockDamage, bool& DoDamage, bool& NoDamage)
{
    // Set all outputs to false by default
    BlockDamage = false;
    DoDamage = false;
    NoDamage = false;

    if (bIsDead)
    {
        NoDamage = true; // Dead characters can not take damage
        return;
    }

    if (!bIsInvincible || ShouldDamageInvincible)
    {
        if (!bIsBlocking || !CanBeBlocked)
        {
            DoDamage = true; // Can take damage
            return;
        }
        else
        {
            BlockDamage = true; // Take damage is blocked
            return;
        }
    }

    NoDamage = true; // cannot take damage
}
