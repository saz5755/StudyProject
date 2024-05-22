// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "../Player/POKPlayerState.h"
#include "../Character/KnightCharacter.h"
#include "../Character/GunnerCharacter.h"
#include "../Character/SoulKnightCharacter.h"
#include "../GameInstance/POKGameInstance.h"
#include "../Player/MainPlayerController.h"
#include "../UI/POKHUD.h"

AMainGameMode::AMainGameMode()
{

	PlayerStateClass = APOKPlayerState::StaticClass();
	DefaultPawnClass = ASoulKnightCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();

	HUDClass = APOKHUD::StaticClass();
}

void AMainGameMode::InitGame(const FString& MapName, const FString& Options, 
	FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	EPlayerType	PlayerType = GetWorld()->GetGameInstance<UPOKGameInstance>()->GetPlayerType();

	/*switch (PlayerType)
	{
	case EPlayerType::Knight:
		DefaultPawnClass = AKnightCharacter::StaticClass();
		break;

	case EPlayerType::Gunner:
		DefaultPawnClass = AGunnerCharacter::StaticClass();
		break;

	case EPlayerType::SoulKnight:
		DefaultPawnClass = ASoulKnightCharacter::StaticClass();
		break;
	}*/
}

APlayerController* AMainGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole,
	const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	APlayerController* result = Super::Login(NewPlayer, InRemoteRole, Portal,
		Options, UniqueId, ErrorMessage);

	UE_LOG(PROJECTOVERKILL, Warning, TEXT("%s"), *Options);

	int32	CommandType;

	// Options 문자열에 Type=값 이 있다면 찾아서 값을 CommandType에
	// 넣어준다.
	if (FParse::Value(*Options, TEXT("Type="), CommandType))
	{
		EPlayerType PlayerType = (EPlayerType)CommandType;

		switch (PlayerType)
		{
		case EPlayerType::Knight:
			DefaultPawnClass = AKnightCharacter::StaticClass();
			break;
		case EPlayerType::Gunner:
			DefaultPawnClass = AGunnerCharacter::StaticClass();
			break;	
		case EPlayerType::SoulKnight:
			DefaultPawnClass = ASoulKnightCharacter::StaticClass();
			break;
		}
	}

	FString	InputName;
	if (FParse::Value(*Options, TEXT("InputName="), InputName))
	{
	}

	return result;
}
