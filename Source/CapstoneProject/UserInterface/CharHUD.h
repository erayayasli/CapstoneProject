// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CharHUD.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API ACharHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	ACharHUD();

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowCrosshair();
	void HideCrosshair();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const class FInteractableData* InteractableData) const;
public:
	// VARIABLES
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UMainMenu> MainMenuClass;
	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UInteractionWidget> InteractionWidgetClass;
	UPROPERTY()
	TObjectPtr<UInteractionWidget> InteractionWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> CrosshairWidget;


	bool bIsMenuVisible;


};
