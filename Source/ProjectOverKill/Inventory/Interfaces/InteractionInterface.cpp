#include "Inventory/Interfaces/InteractionInterface.h"
#include "Player/MainPlayerController.h"

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
