#pragma once

#include "UObject/Interface.h"
#include "HitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTOVERKILL_API IHitInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void GetHit(const FVector& ImpactPoint, AActor* Hitter) = 0;
};
