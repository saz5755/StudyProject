// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameMode/KDTGameModeBase.h"
#include "Actors/Controller/KDTPlayerController.h"

AKDTGameModeBase::AKDTGameModeBase()
{
	PlayerControllerClass = AKDTPlayerController::StaticClass();
}