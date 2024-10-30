// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingItem.h"

void ABuildingItem::Interact_Implementation(ACapstoneProjectCharacter* Character)
{
    Super::Interact_Implementation(Character); // BaseItem class Interact Func
    UE_LOG(LogTemp, Warning, TEXT("Building item: %s"), *this->GetName());
}
