#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CapstoneProject/Interface/InteractInterface.h"
#include "CapstoneProject/DataType/StructsClassesEnums.h"
#include "CapstoneProjectCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class ACharHUD;
class UStatlineComponent;
class USoundCue;
class UAudioComponent;
class UDamageComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

USTRUCT(BlueprintType)
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData() :
		CurrentInteractable(nullptr),
		LastInteractionCheckTime(0.0f)
	{
	};

	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
};


UCLASS(config=Game)
class ACapstoneProjectCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Stat Component: , hunger, thirst, stamina*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
	UStatlineComponent* StatlineComponent;

	/** Damage component for both enemy and player. works on health, heal take damage etc.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
	UDamageComponent* DamageComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* FootstepAudioComponent;

	/**Input Actions - Begin*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleMenuAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SneakAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftClickAction;
	/**Input Actions - END*/

	/** Sound Cues for walking sneaking, running and jumping(landing)*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound Cues", meta = (AllowPrivateAccess = "true"))
	USoundCue* SneakGrassCue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound Cues", meta = (AllowPrivateAccess = "true"))
	USoundCue* WalkGrassCue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound Cues", meta = (AllowPrivateAccess = "true"))
	USoundCue* SprintGrassCue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound Cues", meta = (AllowPrivateAccess = "true"))
	USoundCue* JumpGrassCue;

public:
	ACapstoneProjectCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool CanJump() const;
	void HasJumped();
	bool CanSprint() const;
	void SetSprinting(const bool& IsSprinting);
	void SetSneaking(const bool& IsSneaking);


	//
	void PlayerJump();
	void PlayerEndJump();
	void SprintOn();
	void SprintOff();
	void SneakOn();
	void SneakOff();
	void OnClickedLeftClick();


	// Helper Function
	bool BlockCharacterInput() const;
	void IfSlotsContextMenuOpenClose() const;
protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	

public:
	//We might use this
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	class UItemBase* HoldingItemReference;

private:
	const FVector DefaultHoldingItemLocation = FVector(60.f, 20.f, -30.f);
	const FRotator DefaultHoldingItemRotation = FRotator(0.f, 0.f, 0.f);

public:
	/////////////

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "HUD")
	ACharHUD* HUD;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractInterface> TargetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
	TObjectPtr<class UInventoryComponent> PlayerInventory;

	// interaction properties
	float InteractionCheckFrequency;
	float InteractionCheckDistance;
	FTimerHandle TimerHandle_Interaction;
	FInteractionData InteractionData;


	//FUNCTIONS
	void ToggleMenu();

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();

	void UpdateInteractionWidget() const;
	void DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop);

	void UpdateStatsFromItem(FEffectOnStats AddingValues);

	virtual void Tick(float DeltaSeconds) override;



public:
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };
	FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory; }
	FORCEINLINE FVector GetHoldingItemDefaultLocation() { return DefaultHoldingItemLocation; }
	FORCEINLINE FRotator GetHoldingItemDefaultRotation() { return DefaultHoldingItemRotation; }


};

