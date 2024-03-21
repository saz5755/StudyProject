// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "KDT1GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API UKDT1GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	EPlayerType	mSelectPlayerType;

public:
	void SetPlayerType(EPlayerType Type)
	{
		mSelectPlayerType = Type;
	}

	EPlayerType GetPlayerType()
	{
		return mSelectPlayerType;
	}
};
