// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UI/UICoin.h"
#include "CoinGameState.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API ACoinGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACoinGameState();

	UFUNCTION(BlueprintCallable)
	void GetCoin();

protected:
	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay() override;

protected:
	UUICoin* UICoin = nullptr;
	int32 CoinCount = 0;

private:
	static inline TSubclassOf<UUICoin> CoinWidgetClass;
	static inline UClass* CoinTriggerClass;
};
