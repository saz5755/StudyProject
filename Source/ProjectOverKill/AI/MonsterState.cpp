#include "MonsterState.h"
#include "MonsterPawn.h"

UMonsterState::UMonsterState()
{
}

void UMonsterState::BeginPlay()
{
	Super::BeginPlay();

	const FMonsterData* Data = AMonsterPawn::FindMonsterData(mDataTableRowName);

	if (Data)
	{
		mMoveSpeed = Data->mMoveSpeed;
		mInteractionDistance = Data->mTraceDistance;
		mAttackPoint = Data->mAttackPoint;
		mArmorPoint = Data->mArmorPoint;
		mHP = Data->mHPMax;
		mHPMax = Data->mHPMax;
		mMP = Data->mMPMax;
		mMPMax = Data->mMPMax;
		mAttackDistance = Data->mAttackDistance;
	}
}
