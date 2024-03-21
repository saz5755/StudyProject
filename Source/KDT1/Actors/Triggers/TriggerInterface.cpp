#include "TriggerInterface.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(TriggerInterface)

void ITriggerInterface::Active()
{
	AActor* Actor = Cast<AActor>(this);
	Execute_ReceiveActive(Actor);
}

void ITriggerInterface::Inactive()
{
	AActor* Actor = Cast<AActor>(this);
	Execute_ReceiveInactive(Actor);
}

void ITriggerInterface::InTrigger()
{
	AActor* Actor = Cast<AActor>(this);
	Execute_ReceiveInTrigger(Actor);
}

void ITriggerInterface::OutTrigger()
{
	AActor* Actor = Cast<AActor>(this);
	Execute_ReceiveOutTrigger(Actor);
}
