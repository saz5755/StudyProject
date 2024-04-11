#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

UCLASS()
class PROJECTOVERKILL_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UBehaviorTree* mBehaviourTree;
	UBlackboardData* mBlackboard;

public:
	ADefaultAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
