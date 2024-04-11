#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectTarget.generated.h"

UCLASS()
class PROJECTOVERKILL_API UBTService_DetectTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_DetectTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
