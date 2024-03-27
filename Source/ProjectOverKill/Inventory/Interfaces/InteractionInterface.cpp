// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Interfaces/InteractionInterface.h"

// Add default functionality here for any IInteractionInterface functions that are not pure virtual.

void IInteractionInterface::BeginFocus()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginFocus"));

}

void IInteractionInterface::EndFocus()
{
	UE_LOG(LogTemp, Warning, TEXT("EndFocus"));

}

void IInteractionInterface::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginInteract"));

}

void IInteractionInterface::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("EndInteract"));

}

void IInteractionInterface::Interact(AMainPlayerController* PlayerController)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));

}
