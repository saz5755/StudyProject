// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTOVERKILL_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ADefaultAIController();

protected:
	UBehaviorTree* mBehaviourTree;
	UBlackboardData* mBlackboard;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
