#include "UI/MainMenu.h"

#include "Item/ItemBase.h"
#include "UI/Inventory/ItemDragDropOperation.h"

#include "../Player/MainPlayerController.h"

void UMainMenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();
    PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
}

bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);
    if (PlayerController && ItemDragDrop->SourceItem)
    {
        PlayerController->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
        return true;
    }
    return false;
}
