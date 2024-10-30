// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableItem.h"

void AConsumableItem::Interact_Implementation(ACapstoneProjectCharacter* Character)
{
    Super::Interact_Implementation(Character); // BaseItem class Interact Func
    UE_LOG(LogTemp, Warning, TEXT("Consumed item: %s"), *this->GetName());
}
