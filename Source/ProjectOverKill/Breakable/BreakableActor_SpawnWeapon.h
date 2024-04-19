#pragma once

#include "Breakable/BreakableActor.h"
#include "BreakableActor_SpawnWeapon.generated.h"

UCLASS()
class PROJECTOVERKILL_API ABreakableActor_SpawnWeapon : public ABreakableActor
{
	GENERATED_BODY()

public:

	ABreakableActor_SpawnWeapon();

	virtual void GetHit(const FVector& ImpactPoint, AActor* Hitter) override;
	
};
