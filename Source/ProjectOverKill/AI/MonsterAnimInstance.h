// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	//HitReact
};

UCLASS()
class PROJECTOVERKILL_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterAnimType	mAnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mHitReactMontageArray;

public:
	void ChangeAnimType(EMonsterAnimType Type)
	{
		mAnimType = Type;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();

	UFUNCTION()
	void AnimNotify_HitReact(int32 Index);

	UFUNCTION()
	void AnimNotify_HitEnd();
};
