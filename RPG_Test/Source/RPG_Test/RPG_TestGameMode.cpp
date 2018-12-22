// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPG_TestGameMode.h"
#include "RPG_TestHUD.h"
#include "RPG_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPG_TestGameMode::ARPG_TestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ARPG_TestHUD::StaticClass();
}
