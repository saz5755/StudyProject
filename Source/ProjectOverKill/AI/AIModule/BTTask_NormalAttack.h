#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_NormalAttack.generated.h"

UCLASS()
class PROJECTOVERKILL_API UBTTask_NormalAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_NormalAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
