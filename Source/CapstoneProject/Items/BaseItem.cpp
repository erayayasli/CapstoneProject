// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"

void ABaseItem::Interact_Implementation(ACapstoneProjectCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("BaseItem with %s"), *this->GetName());
}

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
