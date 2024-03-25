// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectGameMode.h"
#include "../Character/SelectCharacter/CharacterSelectPlayerController.h"
#include "../Character/SelectCharacter/CharacterSelectPawn.h"

ACharacterSelectGameMode::ACharacterSelectGameMode()
{
	PlayerControllerClass = ACharacterSelectPlayerController::StaticClass();
	//DefaultPawnClass = ACharacterSelectPawn::StaticClass();
}
