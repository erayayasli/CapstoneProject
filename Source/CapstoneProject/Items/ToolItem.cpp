// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolItem.h"

AToolItem::AToolItem()
{
    SetItemType(EItemType::ToolItem);

}

void AToolItem::Interact_Implementation(ACapstoneProjectCharacter* Character)
{
    Super::Interact_Implementation(Character); // BaseItem class Interact Func
    UE_LOG(LogTemp, Warning, TEXT("Tool item: %s"), *this->GetName());
}
