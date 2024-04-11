#pragma once

#include "MonsterPawn.h"
#include "AIMinion.generated.h"

UCLASS()
class PROJECTOVERKILL_API AAIMinion : public AMonsterPawn
{
	GENERATED_BODY()
	
public:
	AAIMinion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void NormalAttack();
};
