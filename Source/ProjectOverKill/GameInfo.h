// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Engine.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Blueprint/SlateBlueprintLibrary.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "MediaSource.h"
#include "MediaTexture.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(PROJECTOVERKILL, Log, All);

UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	Knight,
	Gunner
};


UCLASS()
class PROJECTOVERKILL_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
