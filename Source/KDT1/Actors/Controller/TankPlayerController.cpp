// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controller/TankPlayerController.h"
#include "Actors/Tank/Tank.h"
#include "Data/Input/BasicInputDataConfig.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	const UTankInputDataConfig* InputDataConfig = GetDefault<UTankInputDataConfig>();
	Subsystem->AddMappingContext(InputDataConfig->DefaultContext, 0);
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UTankInputDataConfig* InputDataConfig = GetDefault<UTankInputDataConfig>();
	EnhancedInputComponent->BindAction(InputDataConfig->Attack, ETriggerEvent::Triggered, this, &ThisClass::OnAttack);
	EnhancedInputComponent->BindAction(InputDataConfig->Zoom, ETriggerEvent::Started, this, &ThisClass::OnZoomIn);
	EnhancedInputComponent->BindAction(InputDataConfig->Zoom, ETriggerEvent::Completed, this, &ThisClass::OnZoomOut);
}

void ATankPlayerController::OnAttack(const FInputActionValue& InputActionValue)
{
	ATank* Tank = GetPawn<ATank>();
	Tank->Attack();
}

void ATankPlayerController::OnZoomIn(const FInputActionValue& InputActionValue)
{
	ATank* Tank = GetPawn<ATank>();
	Tank->ZoomIn();
}

void ATankPlayerController::OnZoomOut(const FInputActionValue& InputActionValue)
{
	ATank* Tank = GetPawn<ATank>();
	Tank->ZoomOut();
}
