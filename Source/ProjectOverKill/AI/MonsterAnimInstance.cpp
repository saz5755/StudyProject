#include "MonsterAnimInstance.h"
#include "MonsterPawn.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mAnimType = EMonsterAnimType::Idle;
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMonsterAnimInstance::AnimNotify_Attack()
{
	AMonsterPawn* Pawn = Cast<AMonsterPawn>(TryGetPawnOwner());

	Pawn->NormalAttack();
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AMonsterPawn* Pawn = Cast<AMonsterPawn>(TryGetPawnOwner());

	Pawn->SetAttackEnd(true);
}

void UMonsterAnimInstance::AnimNotify_DeathEnd()
{
	AMonsterPawn* Pawn = Cast<AMonsterPawn>(TryGetPawnOwner());

	Pawn->OnDissolve();
}

void UMonsterAnimInstance::AnimNotify_HitReact(int32 Index)
{
	if (!Montage_IsPlaying(mHitReactMontageArray[Index]))
	{
		//ChangeAnimType(EMonsterAnimType::HitReact);

		// ��� ��Ű�� ���� ��� ��ġ�� ó������ �ʱ�ȭ �����ش�.
		Montage_SetPosition(mHitReactMontageArray[Index], 0.f);

		// ��������ش�.
		Montage_Play(mHitReactMontageArray[Index]);
	}
}

void UMonsterAnimInstance::AnimNotify_HitEnd()
{
	mAnimType = EMonsterAnimType::Idle;
}



