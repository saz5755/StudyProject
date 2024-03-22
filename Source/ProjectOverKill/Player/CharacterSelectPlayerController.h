// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "CharacterSelectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTOVERKILL_API ACharacterSelectPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACharacterSelectPlayerController();

protected:
	AActor* mHitActor;
	TSubclassOf<UUserWidget>	mSelectWidgetClass;
	class USelectWidget* mSelectWidget;
	EPlayerType		mSelectPlayerType;

public:
	EPlayerType GetPlayerType()
	{
		return mSelectPlayerType;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void OnSelect(const FInputActionValue& InputActionValue);
};
