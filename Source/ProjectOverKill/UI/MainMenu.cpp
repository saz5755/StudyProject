#include "UI/MainMenu.h"

void UMainMenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();
    PlayerController = Cast<AMainPlayerController>(GetOwningPlayerPawn());
}

bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    // cast operation to item drag drop, ensure player is valid, call drop item on player
}
