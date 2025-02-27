// Copyright Epic Games, Inc. All Rights Reserved.

#include "CapstoneProjectCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "CapstoneProject/UserInterface/CharHUD.h"
#include "CapstoneProject/Components/InventoryComponent.h"
#include "CapstoneProject/Items/ItemBase.h"
#include "CapstoneProject/World/Pickup.h"
#include "CapstoneProject/Components/StatlineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "DrawDebugHelpers.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACapstoneProjectCharacter

ACapstoneProjectCharacter::ACapstoneProjectCharacter():
	InteractionCheckFrequency(0.1f),
	InteractionCheckDistance(200.0f)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	PlayerInventory->SetSlotsCapacity(20);
	PlayerInventory->SetWeightCapacity(50.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	StatlineComponent = CreateDefaultSubobject<UStatlineComponent>(TEXT("StatlineComponent"));
	StatlineComponent->SetMovementCompReference(GetCharacterMovement());

	GetCharacterMovement()->MaxWalkSpeed = StatlineComponent->WalkSpeed;
}

void ACapstoneProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	HUD = Cast<ACharHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

}
bool ACapstoneProjectCharacter::CanJump() const
{
	return StatlineComponent->CanJump();
}
void ACapstoneProjectCharacter::HasJumped()
{
	if (StatlineComponent)
	{
		StatlineComponent->HasJumped();
		ACharacter::Jump();
	}
}
bool ACapstoneProjectCharacter::CanSprint() const
{
	return StatlineComponent->CanSprint();
}
void ACapstoneProjectCharacter::SetSprinting(const bool& IsSprinting)
{
	StatlineComponent->SetSprinting(IsSprinting);
}
void ACapstoneProjectCharacter::SetSneaking(const bool& IsSneaking)
{
	//StatlineComponent->SetSneaking(IsSneaking);
}
void ACapstoneProjectCharacter::PlayerJump()
{
	if (BlockCharacterInput())
	{
		return;
	}
	if (CanJump() && !GetMovementComponent()->IsFalling())
	{
		HasJumped();
	}
}
void ACapstoneProjectCharacter::SprintOn()
{
	if (BlockCharacterInput())
	{
		return;
	}
	SetSprinting(true);
}
void ACapstoneProjectCharacter::SprintOff()
{
	if (BlockCharacterInput())
	{
		return;
	}
	SetSprinting(false);
}
void ACapstoneProjectCharacter::SneakOn()
{
	if (BlockCharacterInput())
	{
		return;
	}
	SetSneaking(true);
}
void ACapstoneProjectCharacter::SneakOff()
{
	if (BlockCharacterInput())
	{
		return;
	}
	SetSneaking(false);
}
void ACapstoneProjectCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ACapstoneProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACapstoneProjectCharacter::PlayerJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Interaction
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACapstoneProjectCharacter::BeginInteract);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ACapstoneProjectCharacter::EndInteract);

		// Toggle menu
		EnhancedInputComponent->BindAction(ToggleMenuAction, ETriggerEvent::Started, this, &ACapstoneProjectCharacter::ToggleMenu);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACapstoneProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACapstoneProjectCharacter::Look);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ACapstoneProjectCharacter::SprintOn);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACapstoneProjectCharacter::SprintOff);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

bool ACapstoneProjectCharacter::BlockCharacterInput() const
{
	return HUD->bIsMenuVisible;
}

void ACapstoneProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ACapstoneProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACapstoneProjectCharacter::ToggleMenu()
{
	HUD->ToggleMenu();
}

void ACapstoneProjectCharacter::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart{ GetFirstPersonCameraComponent()->GetComponentLocation() };

	//if (!bAiming)
	//{
	//	InteractionCheckDistance = 200.0f;
	//	TraceStart = GetPawnViewLocation();
	//}
	//else
	//{
	//	InteractionCheckDistance = 250.0f;
	//	TraceStart = FollowCamera->GetComponentLocation();
	//}

	FVector TraceEnd{ TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance) };

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f);

	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());
	if (LookDirection > 0)
	{
		// DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		FHitResult TraceHit;

		if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
		{
			if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
			{
				if (TraceHit.GetActor() != InteractionData.CurrentInteractable)
				{
					FoundInteractable(TraceHit.GetActor());
					return;
				}

				if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
				{
					return;
				}
			}
		}
	}

	NoInteractableFound();
}

void ACapstoneProjectCharacter::FoundInteractable(AActor* NewInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}

	// if we are in this function(FoundInteractable) that means new item we are looking. So we need to end focus with old one if there was
	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);

	TargetInteractable->BeginFocus();
}

void ACapstoneProjectCharacter::NoInteractableFound()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
			EndInteract();
		}

		HUD->HideInteractionWidget();

		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void ACapstoneProjectCharacter::BeginInteract()
{
	// verify nothing has changed with the interactable state since beginning interaction
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();

			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction,
					this,
					&ACapstoneProjectCharacter::Interact,
					TargetInteractable->InteractableData.InteractionDuration,
					false);
			}
		}
	}
}

void ACapstoneProjectCharacter::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void ACapstoneProjectCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}
void ACapstoneProjectCharacter::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}

void ACapstoneProjectCharacter::DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop)
{
	if (PlayerInventory->FindMatchingItem(ItemToDrop))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector SpawnLocation{ GetActorLocation() + (GetActorForwardVector() * 50.0f) };
		const FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

		const int32 RemovedQuantity = PlayerInventory->RemoveAmountOfItem(ItemToDrop, QuantityToDrop);

		APickup* Pickup = GetWorld()->SpawnActor<APickup>(APickup::StaticClass(), SpawnTransform, SpawnParams);

		Pickup->InitializeDrop(ItemToDrop, RemovedQuantity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item to drop was somehow null!"));
	}
}
