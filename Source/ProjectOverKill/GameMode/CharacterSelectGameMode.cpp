// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectGameMode.h"
#include "../Player/CharacterSelectPlayerController.h"
#include "../Player/CharacterSelectPawn.h"

ACharacterSelectGameMode::ACharacterSelectGameMode()
{
	PlayerControllerClass = ACharacterSelectPlayerController::StaticClass();
	//DefaultPawnClass = ACharacterSelectPawn::StaticClass();
}
