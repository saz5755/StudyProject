// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


UCLASS()
class PROJECTOVERKILL_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();

private:
	TSubclassOf<UUserWidget>	mMainWidgetClass;
	class UMainViewportWidget* mMainWidget;
	float	mMoveDir;
	
	bool	mDetectEnable = false;
	float	mDetectTime = 0.f;
	float	mDetectDuration = 4.f;
	float	mDetectDelayTime = 0.f;
	float	mDetectDelay = 0.4f;
	TArray<AActor*>	mDetectActorArray;

public:
	class UMainViewportWidget* GetMainWidget()
	{
		return mMainWidget;
	}

	float GetMoveDir()
	{
		return mMoveDir;
	}

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	void OnLookMouse(const FInputActionValue& InputActionValue);
	void OnMove(const FInputActionValue& InputActionValue);
	void OnAttack(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
	void OnDetect(const FInputActionValue& InputActionValue);
	void OnGhost(const FInputActionValue& InputActionValue);

protected:
	void OnSkill0(const FInputActionValue& InputActionValue);
	void OnSkill1(const FInputActionValue& InputActionValue);
};
