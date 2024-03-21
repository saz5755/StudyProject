// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Controller/KDTPlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API ATankPlayerController : public AKDTPlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnAttack(const FInputActionValue& InputActionValue);
	void OnZoomIn(const FInputActionValue& InputActionValue);
	void OnZoomOut(const FInputActionValue& InputActionValue);
};
