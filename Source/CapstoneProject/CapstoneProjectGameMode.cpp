// Copyright Epic Games, Inc. All Rights Reserved.

#include "CapstoneProjectGameMode.h"
#include "Characters/CapstoneProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACapstoneProjectGameMode::ACapstoneProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
