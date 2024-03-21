#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TriggerInterface.generated.h"

UINTERFACE()
class UTriggerInterface : public UInterface
{
	GENERATED_BODY()
};

class ITriggerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Active"))
	void ReceiveActive();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Inactive"))
	void ReceiveInactive();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "InTrigger"))
	void ReceiveInTrigger();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OutTrigger"))
	void ReceiveOutTrigger();

	virtual void Active();
	virtual void Inactive();
	virtual void InTrigger();
	virtual void OutTrigger();
};