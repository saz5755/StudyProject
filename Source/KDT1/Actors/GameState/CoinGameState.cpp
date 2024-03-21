// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameState/CoinGameState.h"
#include "Kismet/GameplayStatics.h"

ACoinGameState::ACoinGameState()
{
	{
		static ConstructorHelpers::FClassFinder<UUICoin> FindClass(
			TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Trigger/Triggers/Coin/UI_CoinCpp.UI_CoinCpp_C'"));
		if (FindClass.Succeeded() || !CoinWidgetClass)
		{
			CoinWidgetClass = FindClass.Class;
		}
	}
	{
		static ConstructorHelpers::FClassFinder<AActor> FindClass(
			TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Trigger/Triggers/Coin/BP_CoinTrigger.BP_CoinTrigger_C'"));
		if (FindClass.Succeeded())
		{
			CoinTriggerClass = FindClass.Class;
		}
	}
}

void ACoinGameState::GetCoin()
{
	--CoinCount;
	UICoin->GetCoinInfo()->SetRemainCoinCount(CoinCount);

	if (CoinCount == 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("LobbyMap"));
	}
}

void ACoinGameState::BeginPlay()
{
	Super::BeginPlay();

	if (!CoinWidgetClass)
	{
		ensure(false);
		return;
	}

	UICoin = CreateWidget<UUICoin>(GetWorld(), CoinWidgetClass);

	if (!CoinTriggerClass)
	{
		ensure(false);
		return;
	}

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CoinTriggerClass, Actors);
	CoinCount = Actors.Num();
	UICoin->GetCoinInfo()->SetRemainCoinCount(CoinCount);
	
	UICoin->AddToViewport();
}
