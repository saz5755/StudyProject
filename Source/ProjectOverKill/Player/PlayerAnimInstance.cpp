// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "../Character/PlayerCharacter.h"
#include "MainPlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAttackIndex = 0;
	mAttackEnable = true;
	mSkillEnable = true;
	mCanJump = true;

	mAnimType = EPlayerAnimType::Default;

	mAdditiveAlpha = 0.f;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();

		if (IsValid(Movement))
		{
			mMoveSpeed = Movement->Velocity.Length();
			mMoveSpeed /= Movement->MaxWalkSpeed;

			// 캐릭터가 땅을 밟고 있는지 판단한다.
			// IsMovingOnGround : 캐릭터가 땅을 밟고 있으면 true,
			// 아니면 false를 반환한다.
			mOnGround = Movement->IsMovingOnGround();

			if (!mOnGround && mAnimType != EPlayerAnimType::Jump &&
				mAnimType != EPlayerAnimType::Fall)
			{
				mAnimType = EPlayerAnimType::Fall;
			}

			// 만약 기본 상태가 아니라면 공격 상태를 비활성화 한다.
			if (mAnimType != EPlayerAnimType::Default)
			{
				mAttackEnable = false;
			}

			//// 땅을 밟았는데 상태가 Fall 상태일 경우 다 떨어졌다는 것이다.
			if (mOnGround && mAnimType == EPlayerAnimType::Fall)
			{
				mAttackEnable = true;
			}
			if (mAnimType == EPlayerAnimType::Jump)
			{
				mAttackEnable = true;
			}
		}

		// 이 애님인스턴스를 가지고 있는 캐릭터로부터 해당 캐릭터를 컨트롤 하고 있는 플레이어
		// 컨트롤러를 얻어온다.
		AMainPlayerController* Controller = PlayerCharacter->GetController<AMainPlayerController>();

		// 위에서 얻어온 컨트롤러가 유효한지 체크한다.
		if (IsValid(Controller))
		{
			mMoveDir = Controller->GetMoveDir();
		}
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	// mAttackEnable 변수는 공격할 수 있는지를 저장해둔 변수이다.
	// 이 변수의 값이 false 일 경우 공격할 수 없는 상황이므로 공격모션 동작을 취소한다.
	if (!mAttackEnable)
		return;

	// 밑에서 공격을 진행하므로 공격 불가능 상황으로 만들어준다.
	mAttackEnable = false;

	// 몽타주가 재생되고 있는지를 판단한다.
	// Montage_IsPlaying 함수는 재생되고 있을 경우 true, 아니면 false가 반환된다.
	if (!Montage_IsPlaying(mAttackMontageArray[mAttackIndex]))
	{
		// 재생 시키기 전에 재생 위치를 처음으로 초기화 시켜준다.
		Montage_SetPosition(mAttackMontageArray[mAttackIndex], 0.f);

		// 재생시켜준다.
		Montage_Play(mAttackMontageArray[mAttackIndex]);

		// 다음 공격 동작을 재생하기 위해 1 증가시켜준다.
		mAttackIndex = (mAttackIndex + 1) % mAttackMontageArray.Num();
	}
}

void UPlayerAnimInstance::PlayJump()
{
	mCanJump = false;

	mAnimType = EPlayerAnimType::Jump;

	// 점프 리커버리 몽타주가 재생되고 있다면 재생을 중지한다.
	if (Montage_IsPlaying(mJumpRecoveryAdditiveMontage))
	{
		Montage_Stop(0.1f, mJumpRecoveryAdditiveMontage);
		mAdditiveAlpha = 0.f;
	}
}

void UPlayerAnimInstance::AnimNotify_Attack()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	PlayerCharacter->NormalAttack();
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	// 공격 가능상태로 만들어주어서 공격키를 눌렀을때 동작할 수 있게 한다.
	mAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	// 공격 가능상태로 만들어주어서 공격키를 눌렀을때 동작할 수 있게 한다.
	mAttackEnable = true;

	// 공격 인덱스를 0으로 초기화한다.
	mAttackIndex = 0;
}

void UPlayerAnimInstance::PlaySkillMontage(int32 Index)
{
	if (!Montage_IsPlaying(mSkillMontageArray[Index]))
	{
		// 재생 시키기 전에 재생 위치를 처음으로 초기화 시켜준다.
		Montage_SetPosition(mSkillMontageArray[Index], 0.f);

		// 재생시켜준다.
		Montage_Play(mSkillMontageArray[Index]);

		mAnimType = EPlayerAnimType::Skill;

		mAttackEnable = true;
	}
}

void UPlayerAnimInstance::AnimNotify_TransitionFall()
{
	// 점프가 끝나서 애니메이션 타입을 떨어지는 상태로 전환한다.
	mAnimType = EPlayerAnimType::Fall;
	mAttackEnable = true;

}

void UPlayerAnimInstance::AnimNotify_FallEnd()
{
	mAnimType = EPlayerAnimType::Default;

	// 리커버리 Additive를 적용하기 위해 값을 1로 변경한다.
	mAdditiveAlpha = 1.f;

	// 리커버리 동작을 재생한다.
	if (!Montage_IsPlaying(mJumpRecoveryAdditiveMontage))
	{
		Montage_SetPosition(mJumpRecoveryAdditiveMontage, 0.f);

		Montage_Play(mJumpRecoveryAdditiveMontage);
	}

	// 다시 점프를 가능한 상태로 만들어준다.
	mCanJump = true;
}

void UPlayerAnimInstance::AnimNotify_JumpRecoveryEnd()
{
	// 점프 리커버리 동작이 모두 완료가 되었다면 더이상 Additive 를 적용할 필요가
	// 없기 때문에 mAdditiveAlpha 값을 0으로 초기화한다.
	mAdditiveAlpha = 0.f;
}

void UPlayerAnimInstance::AnimNotify_SkillEnable()
{
	mAttackEnable = true;
	mSkillEnable = true;
}

void UPlayerAnimInstance::AnimNotify_SkillEnd()
{
	mAnimType = EPlayerAnimType::Default;

	mAttackEnable = true;
	mSkillEnable = true;

	// 공격 인덱스를 0으로 초기화한다.
	mAttackIndex = 0;
}

void UPlayerAnimInstance::AnimNotify_StepLeft()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	PlayerCharacter->OnStep(true);
}

void UPlayerAnimInstance::AnimNotify_StepRight()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	PlayerCharacter->OnStep(false);
}
