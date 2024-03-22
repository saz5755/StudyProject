// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SelectAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTOVERKILL_API USelectAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USelectAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	mSelect;

public:
	void SetSelect(bool Select)
	{
		mSelect = Select;
	}

public:
	UFUNCTION()
	void AnimNotify_TransitionSelect();
};
