// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"


UCLASS()
class PROJECTOVERKILL_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMainGameMode();

public:
	virtual void InitGame(const FString& MapName, const FString& Options, 
		FString& ErrorMessage);
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole,
		const FString& Portal, const FString& Options, 
		const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
};
