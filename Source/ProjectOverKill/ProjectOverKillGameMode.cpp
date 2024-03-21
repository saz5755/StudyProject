// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectOverKillGameMode.h"
#include "ProjectOverKillCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectOverKillGameMode::AProjectOverKillGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
