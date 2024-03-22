#pragma once

#include "../GameInfo.h"
#include "Engine/GameInstance.h"
#include "POGameInstance.generated.h"

UCLASS()
class PROJECTOVERKILL_API UPOGameInstance : public UGameInstance
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
