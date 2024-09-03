// Copyright Epic Games, Inc. All Rights Reserved.

#include "Action_CombatGameMode.h"
#include "Action_CombatCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAction_CombatGameMode::AAction_CombatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
