#pragma once

#include "AIState.h"
#include "MonsterState.generated.h"

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class PROJECTOVERKILL_API UMonsterState : public UAIState
{
	GENERATED_BODY()

public:
	UMonsterState();
	
public:
	UPROPERTY(EditAnywhere)
	int32		mAttackPoint;

	UPROPERTY(EditAnywhere)
	int32		mArmorPoint;

	UPROPERTY(EditAnywhere)
	int32		mHP;

	UPROPERTY(EditAnywhere)
	int32		mHPMax;

	UPROPERTY(EditAnywhere)
	int32		mMP;

	UPROPERTY(EditAnywhere)
	int32		mMPMax;

	UPROPERTY(EditAnywhere)
	float		mAttackDistance;

protected:
	virtual void BeginPlay() override;
};
