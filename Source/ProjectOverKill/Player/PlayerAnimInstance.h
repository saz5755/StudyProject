// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

// BlueprintType : 블루프린트에서 사용할 수 있는 타입으로 만들어준다.
UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Default,
	Jump,
	Fall,
	Death,
	Skill
};

UCLASS()
class PROJECTOVERKILL_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	mMoveSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	mMoveDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mAttackMontageArray;
	//TArray<UAnimMontage*>

	// 공격 몽타주를 재생하기 위한 인덱스이다.
	int32	mAttackIndex;

	// 현재 공격가능한 상황인지를 판단하는 변수이다.
	bool	mAttackEnable;
	bool	mSkillEnable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerAnimType	mAnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	mOnGround;

	bool	mCanJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* mJumpRecoveryAdditiveMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	mAdditiveAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mSkillMontageArray;

public:
	UPlayerAnimInstance();

public:
	void SetAnimType(EPlayerAnimType Type)
	{
		mAnimType = Type;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void PlayAttackMontage();
	void PlaySkillMontage(int32 Index);
	void PlayJump();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnable();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_TransitionFall();

	UFUNCTION()
	void AnimNotify_FallEnd();

	UFUNCTION()
	void AnimNotify_JumpRecoveryEnd();

	UFUNCTION()
	void AnimNotify_SkillEnable();	
	
	UFUNCTION()
	void AnimNotify_SkillEnd();

	UFUNCTION()
	void AnimNotify_StepLeft();

	UFUNCTION()
	void AnimNotify_StepRight();
};
